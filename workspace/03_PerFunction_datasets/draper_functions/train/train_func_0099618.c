dlm_receive_rcom(struct dlm_ls *ls, struct dlm_rcom *rc, int nodeid)
{
	int lock_size = sizeof(struct dlm_rcom) + sizeof(struct rcom_lock);
	int stop, reply = 0, names = 0, lookup = 0, lock = 0;
	uint32_t status;
	uint64_t seq;

	switch (rc->rc_type) {
	case DLM_RCOM_STATUS_REPLY:
		reply = 1;
		break;
	case DLM_RCOM_NAMES:
		names = 1;
		break;
	case DLM_RCOM_NAMES_REPLY:
		names = 1;
		reply = 1;
		break;
	case DLM_RCOM_LOOKUP:
		lookup = 1;
		break;
	case DLM_RCOM_LOOKUP_REPLY:
		lookup = 1;
		reply = 1;
		break;
	case DLM_RCOM_LOCK:
		lock = 1;
		break;
	case DLM_RCOM_LOCK_REPLY:
		lock = 1;
		reply = 1;
		break;
	};

	spin_lock(&ls->ls_recover_lock);
	status = ls->ls_recover_status;
	stop = test_bit(LSFL_RECOVER_STOP, &ls->ls_flags);
	seq = ls->ls_recover_seq;
	spin_unlock(&ls->ls_recover_lock);

	if (stop && (rc->rc_type != DLM_RCOM_STATUS))
		goto ignore;

	if (reply && (rc->rc_seq_reply != seq))
		goto ignore;

	if (!(status & DLM_RS_NODES) && (names || lookup || lock))
		goto ignore;

	if (!(status & DLM_RS_DIR) && (lookup || lock))
		goto ignore;

	switch (rc->rc_type) {
	case DLM_RCOM_STATUS:
		receive_rcom_status(ls, rc);
		break;

	case DLM_RCOM_NAMES:
		receive_rcom_names(ls, rc);
		break;

	case DLM_RCOM_LOOKUP:
		receive_rcom_lookup(ls, rc);
		break;

	case DLM_RCOM_LOCK:
		if (rc->rc_header.h_length < lock_size)
			goto Eshort;
		receive_rcom_lock(ls, rc);
		break;

	case DLM_RCOM_STATUS_REPLY:
		receive_sync_reply(ls, rc);
		break;

	case DLM_RCOM_NAMES_REPLY:
		receive_sync_reply(ls, rc);
		break;

	case DLM_RCOM_LOOKUP_REPLY:
		receive_rcom_lookup_reply(ls, rc);
		break;

	case DLM_RCOM_LOCK_REPLY:
		if (rc->rc_header.h_length < lock_size)
			goto Eshort;
		dlm_recover_process_copy(ls, rc);
		break;

	default:
		log_error(ls, "receive_rcom bad type %d", rc->rc_type);
	}
	return;

ignore:
	log_limit(ls, "dlm_receive_rcom ignore msg %d "
		  "from %d %llu %llu recover seq %llu sts %x gen %u",
		   rc->rc_type,
		   nodeid,
		   (unsigned long long)rc->rc_seq,
		   (unsigned long long)rc->rc_seq_reply,
		   (unsigned long long)seq,
		   status, ls->ls_generation);
	return;
Eshort:
	log_error(ls, "recovery message %d from %d is too short",
		  rc->rc_type, nodeid);
}
