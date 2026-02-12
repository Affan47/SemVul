static void execlists_dequeue(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;
	struct i915_request **port = execlists->pending;
	struct i915_request ** const last_port = port + execlists->port_mask;
	struct i915_request *last;
	struct rb_node *rb;
	bool submit = false;


	for (rb = rb_first_cached(&execlists->virtual); rb; ) {
		struct virtual_engine *ve =
			rb_entry(rb, typeof(*ve), nodes[engine->id].rb);
		struct i915_request *rq = READ_ONCE(ve->request);

		if (!rq) {
			rb_erase_cached(rb, &execlists->virtual);
			RB_CLEAR_NODE(rb);
			rb = rb_first_cached(&execlists->virtual);
			continue;
		}

		if (!virtual_matches(ve, rq, engine)) {
			rb = rb_next(rb);
			continue;
		}

		break;
	}


	last = last_active(execlists);
	if (last) {
		if (need_preempt(engine, last, rb)) {
			GEM_TRACE("%s: preempting last=%llx:%lld, prio=%d, hint=%d\n",
				  engine->name,
				  last->fence.context,
				  last->fence.seqno,
				  last->sched.attr.priority,
				  execlists->queue_priority_hint);
			record_preemption(execlists);


			ring_set_paused(engine, 1);


			__unwind_incomplete_requests(engine);


			last->hw_context->lrc_desc |= CTX_DESC_FORCE_RESTORE;
			last = NULL;
		} else if (need_timeslice(engine, last) &&
			   timer_expired(&engine->execlists.timer)) {
			GEM_TRACE("%s: expired last=%llx:%lld, prio=%d, hint=%d\n",
				  engine->name,
				  last->fence.context,
				  last->fence.seqno,
				  last->sched.attr.priority,
				  execlists->queue_priority_hint);

			ring_set_paused(engine, 1);
			defer_active(engine);


			last = NULL;
		} else {


			if (!list_is_last(&last->sched.link,
					  &engine->active.requests)) {


				if (!execlists->timer.expires &&
				    need_timeslice(engine, last))
					set_timer_ms(&execlists->timer,
						     timeslice(engine));

				return;
			}
		}
	}

	while (rb) {
		struct virtual_engine *ve =
			rb_entry(rb, typeof(*ve), nodes[engine->id].rb);
		struct i915_request *rq;

		spin_lock(&ve->base.active.lock);

		rq = ve->request;
		if (unlikely(!rq)) {
			spin_unlock(&ve->base.active.lock);
			rb_erase_cached(rb, &execlists->virtual);
			RB_CLEAR_NODE(rb);
			rb = rb_first_cached(&execlists->virtual);
			continue;
		}

		GEM_BUG_ON(rq != ve->request);
		GEM_BUG_ON(rq->engine != &ve->base);
		GEM_BUG_ON(rq->hw_context != &ve->context);

		if (rq_prio(rq) >= queue_prio(execlists)) {
			if (!virtual_matches(ve, rq, engine)) {
				spin_unlock(&ve->base.active.lock);
				rb = rb_next(rb);
				continue;
			}

			if (last && !can_merge_rq(last, rq)) {
				spin_unlock(&ve->base.active.lock);
				return;
			}

			GEM_TRACE("%s: virtual rq=%llx:%lld%s, new engine? %s\n",
				  engine->name,
				  rq->fence.context,
				  rq->fence.seqno,
				  i915_request_completed(rq) ? "!" :
				  i915_request_started(rq) ? "*" :
				  "",
				  yesno(engine != ve->siblings[0]));

			ve->request = NULL;
			ve->base.execlists.queue_priority_hint = INT_MIN;
			rb_erase_cached(rb, &execlists->virtual);
			RB_CLEAR_NODE(rb);

			GEM_BUG_ON(!(rq->execution_mask & engine->mask));
			rq->engine = engine;

			if (engine != ve->siblings[0]) {
				u32 *regs = ve->context.lrc_reg_state;
				unsigned int n;

				GEM_BUG_ON(READ_ONCE(ve->context.inflight));

				if (!intel_engine_has_relative_mmio(engine))
					virtual_update_register_offsets(regs,
									engine);

				if (!list_empty(&ve->context.signals))
					virtual_xfer_breadcrumbs(ve, engine);


				for (n = 1; n < ve->num_siblings; n++) {
					if (ve->siblings[n] == engine) {
						swap(ve->siblings[n],
						     ve->siblings[0]);
						break;
					}
				}

				GEM_BUG_ON(ve->siblings[0] != engine);
			}

			if (__i915_request_submit(rq)) {
				submit = true;
				last = rq;
			}
			i915_request_put(rq);


			if (!submit) {
				spin_unlock(&ve->base.active.lock);
				rb = rb_first_cached(&execlists->virtual);
				continue;
			}
		}

		spin_unlock(&ve->base.active.lock);
		break;
	}

	while ((rb = rb_first_cached(&execlists->queue))) {
		struct i915_priolist *p = to_priolist(rb);
		struct i915_request *rq, *rn;
		int i;

		priolist_for_each_request_consume(rq, rn, p, i) {
			bool merge = true;


			if (last && !can_merge_rq(last, rq)) {


				if (port == last_port)
					goto done;


				if (last->hw_context == rq->hw_context)
					goto done;

				if (i915_request_has_sentinel(last))
					goto done;


				if (ctx_single_port_submission(last->hw_context) ||
				    ctx_single_port_submission(rq->hw_context))
					goto done;

				merge = false;
			}

			if (__i915_request_submit(rq)) {
				if (!merge) {
					*port = execlists_schedule_in(last, port - execlists->pending);
					port++;
					last = NULL;
				}

				GEM_BUG_ON(last &&
					   !can_merge_ctx(last->hw_context,
							  rq->hw_context));

				submit = true;
				last = rq;
			}
		}

		rb_erase_cached(&p->node, &execlists->queue);
		i915_priolist_free(p);
	}

done:


	execlists->queue_priority_hint = queue_prio(execlists);
	GEM_TRACE("%s: queue_priority_hint:%d, submit:%s\n",
		  engine->name, execlists->queue_priority_hint,
		  yesno(submit));

	if (submit) {
		*port = execlists_schedule_in(last, port - execlists->pending);
		execlists->switch_priority_hint =
			switch_prio(engine, *execlists->pending);


		if (!memcmp(execlists->active, execlists->pending,
			    (port - execlists->pending + 1) * sizeof(*port))) {
			do
				execlists_schedule_out(fetch_and_zero(port));
			while (port-- != execlists->pending);

			goto skip_submit;
		}

		memset(port + 1, 0, (last_port - port) * sizeof(*port));
		execlists_submit_ports(engine);

		set_preempt_timeout(engine);
	} else {
skip_submit:
		ring_set_paused(engine, 0);
	}
}
