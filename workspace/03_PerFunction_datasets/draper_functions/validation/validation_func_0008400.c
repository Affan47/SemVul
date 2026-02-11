gfs_replica_list_by_name(const char *path, int *np, char ***hostsp)
{
	gfarm_error_t e;
	struct gfm_replica_list_by_name_closure closure;

	e = gfm_inode_op(path, GFARM_FILE_LOOKUP,
	    gfm_replica_list_by_name_request,
	    gfm_replica_list_by_name_result,
	    gfm_inode_success_op_connection_free,
	    gfm_replica_list_by_name_cleanup,
	    &closure);
	if (e == GFARM_ERR_NO_ERROR) {
		*np = closure.n;
		*hostsp = closure.hosts;
	} else {
		gflog_debug(GFARM_MSG_1001383,
			"gfm_inode_op(%s) failed: %s",
			path,
			gfarm_error_string(e));
	}
	return (e);
}
