_add_clusters(slurmdbd_conn_t *slurmdbd_conn,
			 Buf in_buffer, Buf *out_buffer, uint32_t *uid)
{
	int rc = SLURM_SUCCESS;
	dbd_list_msg_t *get_msg = NULL;
	char *comment = NULL;

	debug2("DBD_ADD_CLUSTERS: called");
	if ((*uid != slurmdbd_conf->slurm_user_id && *uid != 0)
	    && assoc_mgr_get_admin_level(slurmdbd_conn->db_conn, *uid)
	    < SLURMDB_ADMIN_SUPER_USER) {
		comment = "Your user doesn't have privilege to preform this action";
		error("CONN:%u %s", slurmdbd_conn->newsockfd, comment);
		rc = ESLURM_ACCESS_DENIED;
		goto end_it;
	}

	if (slurmdbd_unpack_list_msg(&get_msg, slurmdbd_conn->rpc_version,
				     DBD_ADD_CLUSTERS, in_buffer) !=
	    SLURM_SUCCESS) {
		comment = "Failed to unpack DBD_ADD_CLUSTERS message";
		error("CONN:%u %s", slurmdbd_conn->newsockfd, comment);
		rc = SLURM_ERROR;
		goto end_it;
	}

	rc = acct_storage_g_add_clusters(slurmdbd_conn->db_conn, *uid,
					 get_msg->my_list);
	if (rc != SLURM_SUCCESS)
		comment = "Failed to add cluster.";

end_it:
	slurmdbd_free_list_msg(get_msg);
	*out_buffer = make_dbd_rc_msg(slurmdbd_conn->rpc_version,
				      rc, comment, DBD_ADD_CLUSTERS);
	return rc;
}
