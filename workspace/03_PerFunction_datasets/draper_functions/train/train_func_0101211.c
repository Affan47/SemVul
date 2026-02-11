bnx2i_mtask_xmit(struct iscsi_conn *conn, struct iscsi_task *task)
{
	struct bnx2i_conn *bnx2i_conn = conn->dd_data;
	struct bnx2i_hba *hba = bnx2i_conn->hba;
	struct bnx2i_cmd *cmd = task->dd_data;

	memset(bnx2i_conn->gen_pdu.req_buf, 0, ISCSI_DEF_MAX_RECV_SEG_LEN);

	bnx2i_setup_cmd_wqe_template(cmd);
	bnx2i_conn->gen_pdu.req_buf_size = task->data_count;


	ADD_STATS_64(hba, tx_pdus, 1);
	ADD_STATS_64(hba, tx_bytes, task->data_count);

	if (task->data_count) {
		memcpy(bnx2i_conn->gen_pdu.req_buf, task->data,
		       task->data_count);
		bnx2i_conn->gen_pdu.req_wr_ptr =
			bnx2i_conn->gen_pdu.req_buf + task->data_count;
	}
	cmd->conn = conn->dd_data;
	cmd->scsi_cmd = NULL;
	return bnx2i_iscsi_send_generic_request(task);
}
