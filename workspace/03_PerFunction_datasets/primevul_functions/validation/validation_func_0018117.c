nfs4_layoutget_handle_exception(struct rpc_task *task,
		struct nfs4_layoutget *lgp, struct nfs4_exception *exception)
{
	struct inode *inode = lgp->args.inode;
	struct nfs_server *server = NFS_SERVER(inode);
	struct pnfs_layout_hdr *lo;
	int nfs4err = task->tk_status;
	int err, status = 0;
	LIST_HEAD(head);

	dprintk("--> %s tk_status => %d\n", __func__, -task->tk_status);

	nfs4_sequence_free_slot(&lgp->res.seq_res);

	switch (nfs4err) {
	case 0:
		goto out;


	case -NFS4ERR_LAYOUTUNAVAILABLE:
		status = -ENODATA;
		goto out;


	case -NFS4ERR_BADLAYOUT:
		status = -EOVERFLOW;
		goto out;


	case -NFS4ERR_LAYOUTTRYLATER:
		if (lgp->args.minlength == 0) {
			status = -EOVERFLOW;
			goto out;
		}
		status = -EBUSY;
		break;
	case -NFS4ERR_RECALLCONFLICT:
		status = -ERECALLCONFLICT;
		break;
	case -NFS4ERR_DELEG_REVOKED:
	case -NFS4ERR_ADMIN_REVOKED:
	case -NFS4ERR_EXPIRED:
	case -NFS4ERR_BAD_STATEID:
		exception->timeout = 0;
		spin_lock(&inode->i_lock);
		lo = NFS_I(inode)->layout;

		if (!lo || test_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags) ||
		    !nfs4_stateid_match_other(&lgp->args.stateid, &lo->plh_stateid)) {
			spin_unlock(&inode->i_lock);
			exception->state = lgp->args.ctx->state;
			exception->stateid = &lgp->args.stateid;
			break;
		}


		pnfs_mark_layout_stateid_invalid(lo, &head);
		spin_unlock(&inode->i_lock);
		nfs_commit_inode(inode, 0);
		pnfs_free_lseg_list(&head);
		status = -EAGAIN;
		goto out;
	}

	err = nfs4_handle_exception(server, nfs4err, exception);
	if (!status) {
		if (exception->retry)
			status = -EAGAIN;
		else
			status = err;
	}
out:
	dprintk("<-- %s\n", __func__);
	return status;
}
