backup_locally(struct volume_group *vg)
{
	if (!vg->cmd->backup_params->enabled || !vg->cmd->backup_params->dir) {
		log_warn("WARNING: This metadata update is NOT backed up");
		return 1;
	}

	if (test_mode()) {
		log_verbose("Test mode: Skipping backup of volume group.");
		return 1;
	}

	if (!dm_create_dir(vg->cmd->backup_params->dir))
		return 0;


	if ((access(vg->cmd->backup_params->dir, R_OK | W_OK | X_OK) == -1) &&
	    (errno == EROFS))
		return 0;

	if (!__backup(vg)) {
		log_error("Backup of volume group %s metadata failed.",
			  vg->name);
		return 0;
	}

	return 1;
}
