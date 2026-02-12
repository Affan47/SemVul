static bool can_write_data(struct io *io, void *user_data)
{
	struct bt_att_chan *chan = user_data;
	struct att_send_op *op;
	struct timeout_data *timeout;

	op = pick_next_send_op(chan);
	if (!op)
		return false;

	if (!bt_att_chan_write(chan, op->opcode, op->pdu, op->len)) {
		if (op->callback)
			op->callback(BT_ATT_OP_ERROR_RSP, NULL, 0,
							op->user_data);
		destroy_att_send_op(op);
		return true;
	}


	switch (op->type) {
	case ATT_OP_TYPE_REQ:
		chan->pending_req = op;
		break;
	case ATT_OP_TYPE_IND:
		chan->pending_ind = op;
		break;
	case ATT_OP_TYPE_RSP:

		chan->in_req = false;

	case ATT_OP_TYPE_CMD:
	case ATT_OP_TYPE_NFY:
	case ATT_OP_TYPE_CONF:
	case ATT_OP_TYPE_UNKNOWN:
	default:
		destroy_att_send_op(op);
		return true;
	}

	timeout = new0(struct timeout_data, 1);
	timeout->chan = chan;
	timeout->id = op->id;
	op->timeout_id = timeout_add(ATT_TIMEOUT_INTERVAL, timeout_cb,
								timeout, free);


	return true;
}
