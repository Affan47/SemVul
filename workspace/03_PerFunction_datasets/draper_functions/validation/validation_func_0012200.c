_addto_used_info(slurmdb_association_rec_t *assoc1,
			    slurmdb_association_rec_t *assoc2)
{
	if (!assoc1 || !assoc2)
		return SLURM_ERROR;

	assoc1->usage->grp_used_cpus += assoc2->usage->grp_used_cpus;
	assoc1->usage->grp_used_mem += assoc2->usage->grp_used_mem;
	assoc1->usage->grp_used_nodes += assoc2->usage->grp_used_nodes;
	assoc1->usage->grp_used_wall += assoc2->usage->grp_used_wall;
	assoc1->usage->grp_used_cpu_run_secs +=
		assoc2->usage->grp_used_cpu_run_secs;

	assoc1->usage->used_jobs += assoc2->usage->used_jobs;
	assoc1->usage->used_submit_jobs += assoc2->usage->used_submit_jobs;
	assoc1->usage->usage_raw += assoc2->usage->usage_raw;

	return SLURM_SUCCESS;
}
