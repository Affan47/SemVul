start_thread (TrapContext *context, int unit)
{
	struct hardfileprivdata *hfpd = &hardfpd[unit];

	if (hfpd->thread_running)
		return 1;
	memset (hfpd, 0, sizeof (struct hardfileprivdata));
	hfpd->base = m68k_areg (regs, 6);
	init_comm_pipe (&hfpd->requests, 100, 1);
	uae_sem_init (&hfpd->sync_sem, 0, 0);
	uae_start_thread (_T("hardfile"), hardfile_thread, hfpd, NULL);
	uae_sem_wait (&hfpd->sync_sem);
	return hfpd->thread_running;
}
