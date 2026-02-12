static void handle_conf(struct bt_att_chan *chan, uint8_t *pdu, ssize_t pdu_len)
{
	struct bt_att *att = chan->att;
	struct att_send_op *op = chan->pending_ind;


	if (!op || pdu_len) {
		util_debug(att->debug_callback, att->debug_data,
				"(chan %p) Received unexpected/invalid ATT "
				"confirmation", chan);
		io_shutdown(chan->io);
		return;
	}

	if (op->callback)
		op->callback(BT_ATT_OP_HANDLE_CONF, NULL, 0, op->user_data);

	destroy_att_send_op(op);
	chan->pending_ind = NULL;

	wakeup_chan_writer(chan, NULL);
}
