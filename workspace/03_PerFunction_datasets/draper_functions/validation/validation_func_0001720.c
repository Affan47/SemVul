slurmdb_init_association_rec(slurmdb_association_rec_t *assoc,
					 bool free_it)
{
	if (!assoc)
		return;

	if (free_it)
		_free_assoc_rec_members(assoc);
	memset(assoc, 0, sizeof(slurmdb_association_rec_t));

	assoc->def_qos_id = NO_VAL;
	assoc->is_def = (uint16_t)NO_VAL;

	assoc->grp_cpu_mins = (uint64_t)NO_VAL;
	assoc->grp_cpu_run_mins = (uint64_t)NO_VAL;
	assoc->grp_cpus = NO_VAL;
	assoc->grp_jobs = NO_VAL;
	assoc->grp_mem = NO_VAL;
	assoc->grp_nodes = NO_VAL;
	assoc->grp_submit_jobs = NO_VAL;
	assoc->grp_wall = NO_VAL;

	assoc->lft = NO_VAL;
	assoc->rgt = NO_VAL;


	assoc->max_cpu_mins_pj = (uint64_t)NO_VAL;
	assoc->max_cpu_run_mins = (uint64_t)NO_VAL;
	assoc->max_cpus_pj = NO_VAL;
	assoc->max_jobs = NO_VAL;
	assoc->max_nodes_pj = NO_VAL;
	assoc->max_submit_jobs = NO_VAL;
	assoc->max_wall_pj = NO_VAL;


	assoc->shares_raw = NO_VAL;


}
