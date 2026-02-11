_print_job_dependency(job_info_t * job, int width, bool right_justify,
			char* suffix)
{
	if (job == NULL)
		_print_str("DEPENDENCY", width, right_justify, true);
	else if (job->dependency)
		_print_str(job->dependency, width, right_justify, true);
	else
		_print_str("", width, right_justify, true);
	if (suffix)
		printf("%s", suffix);
	return SLURM_SUCCESS;
}
