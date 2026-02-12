static void execlists_init_reg_state(u32 *regs,
				     const struct intel_context *ce,
				     const struct intel_engine_cs *engine,
				     const struct intel_ring *ring,
				     bool close)
{


	u32 *bbe = set_offsets(regs, reg_offsets(engine), engine);

	if (close) {
		*bbe = MI_BATCH_BUFFER_END;
		if (INTEL_GEN(engine->i915) >= 10)
			*bbe |= BIT(0);
	}

	init_common_reg_state(regs, engine, ring);
	init_ppgtt_reg_state(regs, vm_alias(ce->vm));

	init_wa_bb_reg_state(regs, engine,
			     INTEL_GEN(engine->i915) >= 12 ?
			     GEN12_CTX_BB_PER_CTX_PTR :
			     CTX_BB_PER_CTX_PTR);
}
