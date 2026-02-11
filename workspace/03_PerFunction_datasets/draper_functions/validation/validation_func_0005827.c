nfs4_purge_lease(struct nfs_client *clp)
{
	int status;

	status = nfs4_establish_lease(clp);
	if (status < 0)
		return nfs4_handle_reclaim_lease_error(clp, status);
	clear_bit(NFS4CLNT_PURGE_STATE, &clp->cl_state);
	set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state);
	nfs4_state_start_reclaim_nograce(clp);
	return 0;
}
