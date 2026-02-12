static int selinux_msg_queue_msgsnd(struct kern_ipc_perm *msq, struct msg_msg *msg, int msqflg)
{
	struct ipc_security_struct *isec;
	struct msg_security_struct *msec;
	struct common_audit_data ad;
	u32 sid = current_sid();
	int rc;

	isec = selinux_ipc(msq);
	msec = selinux_msg_msg(msg);


	if (msec->sid == SECINITSID_UNLABELED) {


		rc = security_transition_sid(&selinux_state, sid, isec->sid,
					     SECCLASS_MSG, NULL, &msec->sid);
		if (rc)
			return rc;
	}

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = msq->key;


	rc = avc_has_perm(&selinux_state,
			  sid, isec->sid, SECCLASS_MSGQ,
			  MSGQ__WRITE, &ad);
	if (!rc)

		rc = avc_has_perm(&selinux_state,
				  sid, msec->sid, SECCLASS_MSG,
				  MSG__SEND, &ad);
	if (!rc)

		rc = avc_has_perm(&selinux_state,
				  msec->sid, isec->sid, SECCLASS_MSGQ,
				  MSGQ__ENQUEUE, &ad);

	return rc;
}
