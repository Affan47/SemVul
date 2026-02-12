gen10_init_indirectctx_bb(struct intel_engine_cs *engine, u32 *batch)
{
	int i;


	batch = gen8_emit_pipe_control(batch,
				       PIPE_CONTROL_CS_STALL,
				       0);


	for (i = 0; i < 10; i++)
		*batch++ = MI_NOOP;


	while ((unsigned long)batch % CACHELINE_BYTES)
		*batch++ = MI_NOOP;

	return batch;
}
