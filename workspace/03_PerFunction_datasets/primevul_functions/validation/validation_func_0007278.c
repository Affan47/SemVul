gen12_csb_parse(const struct intel_engine_execlists *execlists, const u32 *csb)
{
	u32 lower_dw = csb[0];
	u32 upper_dw = csb[1];
	bool ctx_to_valid = GEN12_CSB_CTX_VALID(lower_dw);
	bool ctx_away_valid = GEN12_CSB_CTX_VALID(upper_dw);
	bool new_queue = lower_dw & GEN12_CTX_STATUS_SWITCHED_TO_NEW_QUEUE;


	if (!ctx_away_valid || new_queue) {
		GEM_BUG_ON(!ctx_to_valid);
		return true;
	}


	GEM_BUG_ON(GEN12_CTX_SWITCH_DETAIL(upper_dw));
	return false;
}
