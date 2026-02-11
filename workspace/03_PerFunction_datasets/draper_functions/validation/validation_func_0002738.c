_cancel_step_id (void *ci)
{
	int error_code = SLURM_SUCCESS, i;
	job_cancel_info_t *cancel_info = (job_cancel_info_t *)ci;
	uint32_t job_id  = cancel_info->job_id;
	uint32_t step_id = cancel_info->step_id;
	uint16_t sig     = cancel_info->sig;
	bool sig_set = true;

	if (sig == (uint16_t)-1) {
		sig = SIGKILL;
		sig_set = false;
	}

	for (i=0; i<MAX_CANCEL_RETRY; i++) {
		if (sig == SIGKILL)
			verbose("Terminating step %u.%u", job_id, step_id);
		else {
			verbose("Signal %u to step %u.%u",
				sig, job_id, step_id);
		}

		if ((!sig_set) || opt.ctld)
			error_code = slurm_kill_job_step(job_id, step_id, sig);
		else if (sig == SIGKILL)
			error_code = slurm_terminate_job_step(job_id, step_id);
		else
			error_code = slurm_signal_job_step(job_id, step_id,
							   sig);
		if (error_code == 0
		    || (errno != ESLURM_TRANSITION_STATE_NO_UPDATE
			&& errno != ESLURM_JOB_PENDING))
			break;
		verbose("Job is in transistional state, retrying");
		sleep ( 5 + i );
	}
	if (error_code) {
		error_code = slurm_get_errno();
		if ((opt.verbose > 0) || (error_code != ESLURM_ALREADY_DONE ))
			error("Kill job error on job step id %u.%u: %s",
		 		job_id, step_id,
				slurm_strerror(slurm_get_errno()));
	}


	pthread_mutex_lock(   cancel_info->num_active_threads_lock );
	(*(cancel_info->num_active_threads))--;
	pthread_cond_signal(  cancel_info->num_active_threads_cond );
	pthread_mutex_unlock( cancel_info->num_active_threads_lock );

	xfree(cancel_info);
	return NULL;
}
