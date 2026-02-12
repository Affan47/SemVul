static int nfs41_sequence_process(struct rpc_task *task,
		struct nfs4_sequence_res *res)
{
	struct nfs4_session *session;
	struct nfs4_slot *slot = res->sr_slot;
	struct nfs_client *clp;
	int status;
	int ret = 1;

	if (slot == NULL)
		goto out_noaction;

	if (!RPC_WAS_SENT(task) || slot->seq_done)
		goto out;

	session = slot->table->session;

	trace_nfs4_sequence_done(session, res);

	status = res->sr_status;
	if (task->tk_status == -NFS4ERR_DEADSESSION)
		status = -NFS4ERR_DEADSESSION;


	switch (status) {
	case 0:

		nfs4_slot_sequence_acked(slot, slot->seq_nr);

		slot->seq_done = 1;
		clp = session->clp;
		do_renew_lease(clp, res->sr_timestamp);

		nfs41_handle_sequence_flag_errors(clp, res->sr_status_flags,
				!!slot->privileged);
		nfs41_update_target_slotid(slot->table, slot, res);
		break;
	case 1:


		nfs4_slot_sequence_record_sent(slot, slot->seq_nr);
		slot->seq_done = 1;
		goto out;
	case -NFS4ERR_DELAY:


		dprintk("%s: slot=%u seq=%u: Operation in progress\n",
			__func__,
			slot->slot_nr,
			slot->seq_nr);
		nfs4_slot_sequence_acked(slot, slot->seq_nr);
		goto out_retry;
	case -NFS4ERR_RETRY_UNCACHED_REP:
	case -NFS4ERR_SEQ_FALSE_RETRY:


		nfs4_slot_sequence_acked(slot, slot->seq_nr);
		goto retry_new_seq;
	case -NFS4ERR_BADSLOT:


		if (slot->slot_nr < slot->table->target_highest_slotid)
			goto session_recover;
		goto retry_nowait;
	case -NFS4ERR_SEQ_MISORDERED:
		nfs4_slot_sequence_record_sent(slot, slot->seq_nr);


		if ((s32)(slot->seq_nr - slot->seq_nr_last_acked) > 1) {
			slot->seq_nr--;
			goto retry_nowait;
		}


		slot->seq_nr = slot->seq_nr_highest_sent;
		goto out_retry;
	case -NFS4ERR_BADSESSION:
	case -NFS4ERR_DEADSESSION:
	case -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
		goto session_recover;
	default:

		slot->seq_done = 1;
	}
out:

	dprintk("%s: Error %d free the slot \n", __func__, res->sr_status);
out_noaction:
	return ret;
session_recover:
	nfs4_schedule_session_recovery(session, status);
	dprintk("%s ERROR: %d Reset session\n", __func__, status);
	nfs41_sequence_free_slot(res);
	goto out;
retry_new_seq:
	++slot->seq_nr;
retry_nowait:
	if (rpc_restart_call_prepare(task)) {
		nfs41_sequence_free_slot(res);
		task->tk_status = 0;
		ret = 0;
	}
	goto out;
out_retry:
	if (!rpc_restart_call(task))
		goto out;
	rpc_delay(task, NFS4_POLL_RETRY_MAX);
	return 0;
}
