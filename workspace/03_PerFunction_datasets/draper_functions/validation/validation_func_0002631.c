nfs_inode_reclaim_delegation(struct inode *inode, struct rpc_cred *cred,
				  struct nfs_openres *res)
{
	struct nfs_delegation *delegation;
	struct rpc_cred *oldcred = NULL;

	rcu_read_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	if (delegation != NULL) {
		spin_lock(&delegation->lock);
		if (delegation->inode != NULL) {
			nfs4_stateid_copy(&delegation->stateid, &res->delegation);
			delegation->type = res->delegation_type;
			delegation->pagemod_limit = res->pagemod_limit;
			oldcred = delegation->cred;
			delegation->cred = get_rpccred(cred);
			clear_bit(NFS_DELEGATION_NEED_RECLAIM,
				  &delegation->flags);
			spin_unlock(&delegation->lock);
			rcu_read_unlock();
			put_rpccred(oldcred);
			trace_nfs4_reclaim_delegation(inode, res->delegation_type);
		} else {

			spin_unlock(&delegation->lock);
			rcu_read_unlock();
			nfs_inode_set_delegation(inode, cred, res);
		}
	} else {
		rcu_read_unlock();
	}
}
