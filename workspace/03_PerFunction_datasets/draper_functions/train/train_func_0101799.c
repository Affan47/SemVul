create_job_record(int *error_code)
{
	struct job_record  *job_ptr;
	struct job_details *detail_ptr;

	if (job_count >= slurmctld_conf.max_job_cnt) {
		error("create_job_record: job_count exceeds MaxJobCount limit "
		      "configured");
		*error_code = EAGAIN;
		return NULL;
	}

	job_count++;
	*error_code = 0;
	last_job_update = time(NULL);

	job_ptr    = (struct job_record *) xmalloc(sizeof(struct job_record));
	detail_ptr = (struct job_details *)xmalloc(sizeof(struct job_details));

	job_ptr->magic = JOB_MAGIC;
	job_ptr->array_task_id = NO_VAL;
	job_ptr->details = detail_ptr;
	job_ptr->prio_factors = xmalloc(sizeof(priority_factors_object_t));
	job_ptr->step_list = list_create(NULL);

	xassert (detail_ptr->magic = DETAILS_MAGIC);
	detail_ptr->submit_time = time(NULL);
	job_ptr->requid = -1;

	(void) list_append(job_list, job_ptr);

	return job_ptr;
}
