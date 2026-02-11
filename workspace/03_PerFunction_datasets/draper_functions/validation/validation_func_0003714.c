nfs4_handle_migration(struct nfs_client *clp)
{
	const struct nfs4_state_maintenance_ops *ops =
				clp->cl_mvops->state_renewal_ops;
	struct nfs_server *server;
	struct rpc_cred *cred;

	dprintk("%s: migration reported on \"%s\"\n", __func__,
			clp->cl_hostname);

	spin_lock(&clp->cl_lock);
	cred = ops->get_state_renewal_cred_locked(clp);
	spin_unlock(&clp->cl_lock);
	if (cred == NULL)
		return -NFS4ERR_NOENT;

	clp->cl_mig_gen++;
restart:
	rcu_read_lock();
	list_for_each_entry_rcu(server, &clp->cl_superblocks, client_link) {
		int status;

		if (server->mig_gen == clp->cl_mig_gen)
			continue;
		server->mig_gen = clp->cl_mig_gen;

		if (!test_and_clear_bit(NFS_MIG_IN_TRANSITION,
						&server->mig_status))
			continue;

		rcu_read_unlock();
		status = nfs4_try_migration(server, cred);
		if (status < 0) {
			put_rpccred(cred);
			return status;
		}
		goto restart;
	}
	rcu_read_unlock();
	put_rpccred(cred);
	return 0;
}
