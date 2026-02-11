rport_fast_io_fail_timedout(struct work_struct *work)
{
	struct srp_rport *rport = container_of(to_delayed_work(work),
					struct srp_rport, fast_io_fail_work);
	struct Scsi_Host *shost = rport_to_shost(rport);

	pr_info("fast_io_fail_tmo expired for SRP %s / %s.\n",
		dev_name(&rport->dev), dev_name(&shost->shost_gendev));

	mutex_lock(&rport->mutex);
	if (rport->state == SRP_RPORT_BLOCKED)
		__rport_fail_io_fast(rport);
	mutex_unlock(&rport->mutex);
}
