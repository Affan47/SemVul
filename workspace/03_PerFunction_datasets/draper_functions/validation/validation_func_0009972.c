log_alter_with_fp(log_options_t opt, log_facility_t fac, FILE *fp_in)
{
	int rc = 0;
	slurm_mutex_lock(&log_lock);
	rc = _log_init(NULL, opt, fac, NULL);
	if (log->logfp)
		fclose(log->logfp);
	log->logfp = fp_in;
	if (log->logfp) {
		int fd;
		if ((fd = fileno(log->logfp)) < 0)
			log->logfp = NULL;


	}
	slurm_mutex_unlock(&log_lock);
	return rc;
}
