static void reset_active(struct i915_request *rq,
			 struct intel_engine_cs *engine)
{
	struct intel_context * const ce = rq->hw_context;
	u32 head;


	GEM_TRACE("%s(%s): { rq=%llx:%lld }\n",
		  __func__, engine->name, rq->fence.context, rq->fence.seqno);


	if (i915_request_completed(rq))
		head = rq->tail;
	else
		head = active_request(ce->timeline, rq)->head;
	ce->ring->head = intel_ring_wrap(ce->ring, head);
	intel_ring_update_space(ce->ring);


	restore_default_state(ce, engine);
	__execlists_update_reg_state(ce, engine);


	ce->lrc_desc |= CTX_DESC_FORCE_RESTORE;
}
