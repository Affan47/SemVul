lam_ssi_boot_slurm_init(lam_ssi_boot_location_t where, int *priority)
{
  int node_id;


  *priority = lam_ssi_base_param_lookup_int(param_priority);
  if (*priority < 0)
    return NULL;


  if (getenv("SLURM_JOBID") == NULL) {
    if (lam_ssi_boot_verbose >= 5)
      lam_debug(lam_ssi_boot_did, "slurm: not running under SLURM");
    *priority = -1;
    return NULL;
  }


  node_id = lam_ssi_boot_slurm_get_nodeid(NULL);
  if (where == LAM_SSI_BOOT_LOCATION_ROOT &&
      (node_id != 0 && getenv("SLURM_NODEID") != NULL)) {
    if (lam_ssi_boot_verbose >= 5)
      lam_debug(lam_ssi_boot_did,
                "slurm: boot agent on SLURM node %d exiting", node_id);
    lamlog("slurm agent on node %d exiting\n", node_id);
    exit(-1);
  }


  if (lam_ssi_boot_verbose >= 5) {
    lam_debug(lam_ssi_boot_did, "slurm: module initializing");
    lam_debug(lam_ssi_boot_did, "slurm:verbose: %d",
	      lam_ssi_boot_verbose);
    lam_debug(lam_ssi_boot_did, "slurm:priority: %d", *priority);
    lam_debug(lam_ssi_boot_did, "slurm:job_id: %s",
              getenv("SLURM_JOBID"));
  }


  return &module_actions;
}
