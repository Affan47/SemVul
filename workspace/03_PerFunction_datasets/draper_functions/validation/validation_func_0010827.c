select_p_reconfigure(void)
{
	ListIterator job_iterator;
	struct job_record *job_ptr;
	int rc = SLURM_SUCCESS;

	info("cons_res: select_p_reconfigure");
	select_debug_flags = slurm_get_debug_flags();


	job_preemption_enabled = false;
	job_preemption_killing = false;
	job_preemption_tested  = false;
	rc = select_p_node_init(node_record_table_ptr, node_record_count);
	if (rc != SLURM_SUCCESS)
		return rc;


	job_iterator = list_iterator_create(job_list);
	if (job_iterator == NULL)
		fatal ("memory allocation failure");
	while ((job_ptr = (struct job_record *) list_next(job_iterator))) {
		if (IS_JOB_RUNNING(job_ptr)) {

			_add_job_to_res(job_ptr, 0);
		} else if (IS_JOB_SUSPENDED(job_ptr)) {

			_add_job_to_res(job_ptr, 2);
		}
	}
	list_iterator_destroy(job_iterator);
	select_state_initializing = false;

	return SLURM_SUCCESS;
}
