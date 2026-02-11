select_g_job_expand(struct job_record *from_job_ptr,
			       struct job_record *to_job_ptr)
{
	if (slurm_select_init(0) < 0)
		return -1;

	return (*(ops[select_context_default].job_expand))
		(from_job_ptr, to_job_ptr);
}
