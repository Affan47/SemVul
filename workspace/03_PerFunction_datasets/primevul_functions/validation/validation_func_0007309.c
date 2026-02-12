static u32 *gen8_init_indirectctx_bb(struct intel_engine_cs *engine, u32 *batch)
{

	*batch++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;


	if (IS_BROADWELL(engine->i915))
		batch = gen8_emit_flush_coherentl3_wa(engine, batch);


	batch = gen8_emit_pipe_control(batch,
				       PIPE_CONTROL_FLUSH_L3 |
				       PIPE_CONTROL_STORE_DATA_INDEX |
				       PIPE_CONTROL_CS_STALL |
				       PIPE_CONTROL_QW_WRITE,
				       LRC_PPHWSP_SCRATCH_ADDR);

	*batch++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;


	while ((unsigned long)batch % CACHELINE_BYTES)
		*batch++ = MI_NOOP;


	return batch;
}
