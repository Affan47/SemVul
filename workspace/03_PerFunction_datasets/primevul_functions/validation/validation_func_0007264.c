void intel_lr_context_reset(struct intel_engine_cs *engine,
			    struct intel_context *ce,
			    u32 head,
			    bool scrub)
{
	GEM_BUG_ON(!intel_context_is_pinned(ce));


	if (scrub)
		restore_default_state(ce, engine);


	ce->ring->head = head;
	intel_ring_update_space(ce->ring);

	__execlists_update_reg_state(ce, engine);
}
