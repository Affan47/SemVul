static void __execlists_reset(struct intel_engine_cs *engine, bool stalled)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;
	struct intel_context *ce;
	struct i915_request *rq;

	mb();
	clflush(execlists->csb_write);
	mb();

	process_csb(engine);


	reset_csb_pointers(engine);


	rq = execlists_active(execlists);
	if (!rq)
		goto unwind;


	GEM_BUG_ON(!intel_engine_pm_is_awake(engine));

	ce = rq->hw_context;
	GEM_BUG_ON(!i915_vma_is_pinned(ce->state));

	if (i915_request_completed(rq)) {

		ce->ring->head = intel_ring_wrap(ce->ring, rq->tail);
		goto out_replay;
	}


	GEM_BUG_ON(i915_active_is_idle(&ce->active));
	rq = active_request(ce->timeline, rq);
	ce->ring->head = intel_ring_wrap(ce->ring, rq->head);
	GEM_BUG_ON(ce->ring->head == ce->ring->tail);


	if (!i915_request_started(rq))
		goto out_replay;


	__i915_request_reset(rq, stalled);
	if (!stalled)
		goto out_replay;


	GEM_BUG_ON(!intel_context_is_pinned(ce));
	restore_default_state(ce, engine);

out_replay:
	GEM_TRACE("%s replay {head:%04x, tail:%04x}\n",
		  engine->name, ce->ring->head, ce->ring->tail);
	intel_ring_update_space(ce->ring);
	__execlists_reset_reg_state(ce, engine);
	__execlists_update_reg_state(ce, engine);
	ce->lrc_desc |= CTX_DESC_FORCE_RESTORE;

unwind:

	cancel_port_requests(execlists);
	__unwind_incomplete_requests(engine);
}
