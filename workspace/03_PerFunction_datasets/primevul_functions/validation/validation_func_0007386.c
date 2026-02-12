static u64 execlists_update_context(struct i915_request *rq)
{
	struct intel_context *ce = rq->hw_context;
	u64 desc = ce->lrc_desc;
	u32 tail;


	tail = intel_ring_set_tail(rq->ring, rq->tail);
	if (unlikely(ce->lrc_reg_state[CTX_RING_TAIL] == tail))
		desc |= CTX_DESC_FORCE_RESTORE;
	ce->lrc_reg_state[CTX_RING_TAIL] = tail;
	rq->tail = rq->wa_tail;


	mb();


	if (IS_TGL_REVID(rq->i915, TGL_REVID_A0, TGL_REVID_A0))
		desc |= CTX_DESC_FORCE_RESTORE;

	ce->lrc_desc &= ~CTX_DESC_FORCE_RESTORE;
	return desc;
}
