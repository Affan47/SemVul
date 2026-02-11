i915_ring_seqno_info(struct seq_file *m,
				 struct intel_engine_cs *engine)
{
	seq_printf(m, "Current sequence (%s): %x\n",
		   engine->name, engine->get_seqno(engine));
	seq_printf(m, "Current user interrupts (%s): %x\n",
		   engine->name, READ_ONCE(engine->user_interrupts));
}
