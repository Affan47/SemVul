license_job_get(struct job_record *job_ptr)
{
	ListIterator iter;
	licenses_t *license_entry, *match;
	int rc = SLURM_SUCCESS;

	if (!job_ptr->license_list)
		return rc;

	last_license_update = time(NULL);

	slurm_mutex_lock(&license_mutex);
	iter = list_iterator_create(job_ptr->license_list);
	while ((license_entry = (licenses_t *) list_next(iter))) {
		match = list_find_first(license_list, _license_find_rec,
			license_entry->name);
		if (match) {
			match->used += license_entry->total;
			license_entry->used += license_entry->total;
		} else {
			error("could not find license %s for job %u",
			      license_entry->name, job_ptr->job_id);
			rc = SLURM_ERROR;
		}
	}
	list_iterator_destroy(iter);
	_licenses_print("acquire_license", license_list, job_ptr->job_id);
	slurm_mutex_unlock(&license_mutex);
	return rc;
}
