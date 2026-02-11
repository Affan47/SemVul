kgdb_arch_remove_breakpoint(struct kgdb_bkpt *bpt)
{
#ifdef CONFIG_DEBUG_RODATA
	int err;
	char opc[BREAK_INSTR_SIZE];

	if (bpt->type != BP_POKE_BREAKPOINT)
		goto knl_write;


	if (mutex_is_locked(&text_mutex))
		goto knl_write;
	text_poke((void *)bpt->bpt_addr, bpt->saved_instr, BREAK_INSTR_SIZE);
	err = probe_kernel_read(opc, (char *)bpt->bpt_addr, BREAK_INSTR_SIZE);
	if (err || memcmp(opc, bpt->saved_instr, BREAK_INSTR_SIZE))
		goto knl_write;
	return err;
knl_write:
#endif
	return probe_kernel_write((char *)bpt->bpt_addr,
				  (char *)bpt->saved_instr, BREAK_INSTR_SIZE);
}
