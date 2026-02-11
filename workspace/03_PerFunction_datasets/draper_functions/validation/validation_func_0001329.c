nfs_delegations_present(struct nfs_client *clp)
{
	struct nfs_server *server;
	int ret = 0;

	rcu_read_lock();
	list_for_each_entry_rcu(server, &clp->cl_superblocks, client_link)
		if (!list_empty(&server->delegations)) {
			ret = 1;
			break;
		}
	rcu_read_unlock();
	return ret;
}
