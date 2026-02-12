static void process_csb(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;
	const u32 * const buf = execlists->csb_status;
	const u8 num_entries = execlists->csb_size;
	u8 head, tail;


	GEM_BUG_ON(!tasklet_is_locked(&execlists->tasklet) &&
		   !reset_in_progress(execlists));
	GEM_BUG_ON(!intel_engine_in_execlists_submission_mode(engine));


	head = execlists->csb_head;
	tail = READ_ONCE(*execlists->csb_write);
	GEM_TRACE("%s cs-irq head=%d, tail=%d\n", engine->name, head, tail);
	if (unlikely(head == tail))
		return;


	rmb();

	do {
		bool promote;

		if (++head == num_entries)
			head = 0;


		GEM_TRACE("%s csb[%d]: status=0x%08x:0x%08x\n",
			  engine->name, head,
			  buf[2 * head + 0], buf[2 * head + 1]);

		if (INTEL_GEN(engine->i915) >= 12)
			promote = gen12_csb_parse(execlists, buf + 2 * head);
		else
			promote = gen8_csb_parse(execlists, buf + 2 * head);
		if (promote) {
			struct i915_request * const *old = execlists->active;


			WRITE_ONCE(execlists->active, execlists->pending);
			set_timeslice(engine);

			if (!inject_preempt_hang(execlists))
				ring_set_paused(engine, 0);


			trace_ports(execlists, "preempted", old);
			while (*old)
				execlists_schedule_out(*old++);


			GEM_BUG_ON(!assert_pending_valid(execlists, "promote"));
			WRITE_ONCE(execlists->active,
				   memcpy(execlists->inflight,
					  execlists->pending,
					  execlists_num_ports(execlists) *
					  sizeof(*execlists->pending)));

			WRITE_ONCE(execlists->pending[0], NULL);
		} else {
			GEM_BUG_ON(!*execlists->active);


			trace_ports(execlists, "completed", execlists->active);


			GEM_BUG_ON(!i915_request_completed(*execlists->active) &&
				   !reset_in_progress(execlists));
			execlists_schedule_out(*execlists->active++);

			GEM_BUG_ON(execlists->active - execlists->inflight >
				   execlists_num_ports(execlists));
		}
	} while (head != tail);

	execlists->csb_head = head;


	invalidate_csb_entries(&buf[0], &buf[num_entries - 1]);
}
