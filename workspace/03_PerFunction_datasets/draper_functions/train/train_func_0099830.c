iscsi_scsi_cmd_rx_start(struct iscsi_connection *conn)
{
	struct iscsi_cmd *req = (struct iscsi_cmd *) &conn->req.bhs;
	struct iscsi_task *task;
	int ahs_len, imm_len, data_len, ext_len;

	ahs_len = req->hlength * 4;
	imm_len = roundup(ntoh24(req->dlength), conn->tp->data_padding);
	data_len = roundup(ntohl(req->data_length), conn->tp->data_padding);

	dprintf("%u %x %d %d %d %x %x\n", conn->session->tsih,
		req->cdb[0], ahs_len, imm_len, data_len,
		req->flags & ISCSI_FLAG_CMD_ATTR_MASK, req->itt);

	ext_len = ahs_len ? sizeof(req->cdb) + ahs_len : 0;

	task = iscsi_alloc_task(conn, ext_len, max(imm_len, data_len));
	if (task)
		conn->rx_task = task;
	else
		return -ENOMEM;

	task->tag = req->itt;

	if (ahs_len) {
		task->ahs = (uint8_t *) task->extdata + sizeof(req->cdb);
		conn->req.ahs = task->ahs;
		conn->req.data = task->data;
	} else if (data_len)
		conn->req.data = task->data;

	if (req->flags & ISCSI_FLAG_CMD_WRITE) {
		task->offset = ntoh24(req->dlength);
		task->r2t_count = ntohl(req->data_length) - task->offset;
		task->unsol_count = !(req->flags & ISCSI_FLAG_CMD_FINAL);

		dprintf("%d %d %d %d\n", conn->rx_size, task->r2t_count,
			task->unsol_count, task->offset);
	}

	list_add(&task->c_hlist, &conn->session->cmd_list);
	return 0;
}
