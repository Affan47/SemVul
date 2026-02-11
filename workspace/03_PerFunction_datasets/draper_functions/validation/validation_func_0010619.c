iscsit_send_r2t(
	struct iscsi_cmd *cmd,
	struct iscsi_conn *conn)
{
	int tx_size = 0;
	struct iscsi_r2t *r2t;
	struct iscsi_r2t_rsp *hdr;
	int ret;

	r2t = iscsit_get_r2t_from_list(cmd);
	if (!r2t)
		return -1;

	hdr			= (struct iscsi_r2t_rsp *) cmd->pdu;
	memset(hdr, 0, ISCSI_HDR_LEN);
	hdr->opcode		= ISCSI_OP_R2T;
	hdr->flags		|= ISCSI_FLAG_CMD_FINAL;
	int_to_scsilun(cmd->se_cmd.orig_fe_lun,
			(struct scsi_lun *)&hdr->lun);
	hdr->itt		= cmd->init_task_tag;
	r2t->targ_xfer_tag	= session_get_next_ttt(conn->sess);
	hdr->ttt		= cpu_to_be32(r2t->targ_xfer_tag);
	hdr->statsn		= cpu_to_be32(conn->stat_sn);
	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_read(&conn->sess->max_cmd_sn));
	hdr->r2tsn		= cpu_to_be32(r2t->r2t_sn);
	hdr->data_offset	= cpu_to_be32(r2t->offset);
	hdr->data_length	= cpu_to_be32(r2t->xfer_len);

	cmd->iov_misc[0].iov_base	= cmd->pdu;
	cmd->iov_misc[0].iov_len	= ISCSI_HDR_LEN;
	tx_size += ISCSI_HDR_LEN;

	if (conn->conn_ops->HeaderDigest) {
		u32 *header_digest = (u32 *)&cmd->pdu[ISCSI_HDR_LEN];

		iscsit_do_crypto_hash_buf(&conn->conn_tx_hash, hdr,
				ISCSI_HDR_LEN, 0, NULL, (u8 *)header_digest);

		cmd->iov_misc[0].iov_len += ISCSI_CRC_LEN;
		tx_size += ISCSI_CRC_LEN;
		pr_debug("Attaching CRC32 HeaderDigest for R2T"
			" PDU 0x%08x\n", *header_digest);
	}

	pr_debug("Built %sR2T, ITT: 0x%08x, TTT: 0x%08x, StatSN:"
		" 0x%08x, R2TSN: 0x%08x, Offset: %u, DDTL: %u, CID: %hu\n",
		(!r2t->recovery_r2t) ? "" : "Recovery ", cmd->init_task_tag,
		r2t->targ_xfer_tag, ntohl(hdr->statsn), r2t->r2t_sn,
			r2t->offset, r2t->xfer_len, conn->cid);

	cmd->iov_misc_count = 1;
	cmd->tx_size = tx_size;

	spin_lock_bh(&cmd->r2t_lock);
	r2t->sent_r2t = 1;
	spin_unlock_bh(&cmd->r2t_lock);

	ret = iscsit_send_tx_data(cmd, conn, 1);
	if (ret < 0) {
		iscsit_tx_thread_wait_for_tcp(conn);
		return ret;
	}

	spin_lock_bh(&cmd->dataout_timeout_lock);
	iscsit_start_dataout_timer(cmd, conn);
	spin_unlock_bh(&cmd->dataout_timeout_lock);

	return 0;
}
