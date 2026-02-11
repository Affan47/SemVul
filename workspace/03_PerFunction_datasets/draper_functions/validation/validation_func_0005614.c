license_job_merge(struct job_record *job_ptr)
{
	bool valid;

	FREE_NULL_LIST(job_ptr->license_list);
	job_ptr->license_list = _build_license_list(job_ptr->licenses, &valid);
	xfree(job_ptr->licenses);
	job_ptr->licenses = _build_license_string(job_ptr->license_list);
}
