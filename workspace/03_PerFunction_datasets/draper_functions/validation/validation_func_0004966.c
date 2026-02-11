filesys_start_thread (UnitInfo *ui, int nr)
{
	ui->unit_pipe = 0;
	ui->back_pipe = 0;
	ui->reset_state = FS_STARTUP;
	if (!isrestore ()) {
		ui->startup = 0;
		ui->self = 0;
	}
#ifdef UAE_FILESYS_THREADS
	if (is_virtual (nr)) {
		ui->unit_pipe = xmalloc (smp_comm_pipe, 1);
		ui->back_pipe = xmalloc (smp_comm_pipe, 1);
		init_comm_pipe (ui->unit_pipe, 100, 3);
		init_comm_pipe (ui->back_pipe, 100, 1);
#ifdef FSUAE
		if (!uae_deterministic_mode()) {
#endif
		uae_start_thread (_T("filesys"), filesys_thread, (void *)ui, &ui->tid);
#ifdef FSUAE
		}
#endif
	}
#endif
	if (isrestore ()) {
		if (ui->unit_type == UNIT_CDFS) {
			mount_cd (ui, nr, NULL, &ui->self->rootnode.uniq_external);
		}
		startup_update_unit (ui->self, ui);
	}
}
