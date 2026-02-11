esas2r_release(struct Scsi_Host *sh)
{
	esas2r_log_dev(ESAS2R_LOG_INFO, &(sh->shost_gendev),
		       "esas2r_release() called");

	esas2r_cleanup(sh);
	if (sh->irq)
		free_irq(sh->irq, NULL);
	scsi_unregister(sh);
	return 0;
}
