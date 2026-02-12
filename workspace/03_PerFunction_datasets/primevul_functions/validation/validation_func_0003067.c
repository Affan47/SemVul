static int ff_layout_async_handle_error_v4(struct rpc_task *task,
					   struct nfs4_state *state,
					   struct nfs_client *clp,
					   struct pnfs_layout_segment *lseg,
					   u32 idx)
{
	struct pnfs_layout_hdr *lo = lseg->pls_layout;
	struct inode *inode = lo->plh_inode;
	struct nfs4_deviceid_node *devid = FF_LAYOUT_DEVID_NODE(lseg, idx);
	struct nfs4_slot_table *tbl = &clp->cl_session->fc_slot_table;

	switch (task->tk_status) {
	case -NFS4ERR_BADSESSION:
	case -NFS4ERR_BADSLOT:
	case -NFS4ERR_BAD_HIGH_SLOT:
	case -NFS4ERR_DEADSESSION:
	case -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
	case -NFS4ERR_SEQ_FALSE_RETRY:
	case -NFS4ERR_SEQ_MISORDERED:
		dprintk("%s ERROR %d, Reset session. Exchangeid "
			"flags 0x%x\n", __func__, task->tk_status,
			clp->cl_exchange_flags);
		nfs4_schedule_session_recovery(clp->cl_session, task->tk_status);
		break;
	case -NFS4ERR_DELAY:
	case -NFS4ERR_GRACE:
		rpc_delay(task, FF_LAYOUT_POLL_RETRY_MAX);
		break;
	case -NFS4ERR_RETRY_UNCACHED_REP:
		break;

	case -NFS4ERR_PNFS_NO_LAYOUT:
	case -ESTALE:
	case -EBADHANDLE:
	case -EISDIR:
	case -NFS4ERR_FHEXPIRED:
	case -NFS4ERR_WRONG_TYPE:
		dprintk("%s Invalid layout error %d\n", __func__,
			task->tk_status);


		pnfs_destroy_layout(NFS_I(inode));
		rpc_wake_up(&tbl->slot_tbl_waitq);
		goto reset;

	case -ECONNREFUSED:
	case -EHOSTDOWN:
	case -EHOSTUNREACH:
	case -ENETUNREACH:
	case -EIO:
	case -ETIMEDOUT:
	case -EPIPE:
		dprintk("%s DS connection error %d\n", __func__,
			task->tk_status);
		nfs4_delete_deviceid(devid->ld, devid->nfs_client,
				&devid->deviceid);
		rpc_wake_up(&tbl->slot_tbl_waitq);
		fallthrough;
	default:
		if (ff_layout_avoid_mds_available_ds(lseg))
			return -NFS4ERR_RESET_TO_PNFS;
reset:
		dprintk("%s Retry through MDS. Error %d\n", __func__,
			task->tk_status);
		return -NFS4ERR_RESET_TO_MDS;
	}
	task->tk_status = 0;
	return -EAGAIN;
}
