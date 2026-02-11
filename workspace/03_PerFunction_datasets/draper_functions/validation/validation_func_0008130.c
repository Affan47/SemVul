slurm_step_ctx_params_t_init (slurm_step_ctx_params_t *ptr)
{
	char *jobid_str;


	memset(ptr, 0, sizeof(slurm_step_ctx_params_t));


	ptr->relative = (uint16_t)NO_VAL;
	ptr->task_dist = SLURM_DIST_CYCLIC;
	ptr->plane_size = (uint16_t)NO_VAL;
	ptr->resv_port_cnt = (uint16_t)NO_VAL;

	ptr->uid = getuid();

	if ((jobid_str = getenv("SLURM_JOB_ID")) != NULL) {
		ptr->job_id = (uint32_t)atol(jobid_str);
	} else if ((jobid_str = getenv("SLURM_JOBID")) != NULL) {

		ptr->job_id = (uint32_t)atol(jobid_str);
	} else {
		ptr->job_id = (uint32_t)NO_VAL;
	}
}
