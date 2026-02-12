static struct att_send_op *pick_next_send_op(struct bt_att_chan *chan)
{
	struct bt_att *att = chan->att;
	struct att_send_op *op;


	op = queue_pop_head(chan->queue);
	if (op)
		return op;


	op = queue_peek_head(att->write_queue);
	if (op && op->len <= chan->mtu)
		return queue_pop_head(att->write_queue);


	if (!chan->pending_req) {
		op = queue_peek_head(att->req_queue);
		if (op && op->len <= chan->mtu)
			return queue_pop_head(att->req_queue);
	}


	if (!chan->pending_ind) {
		op = queue_peek_head(att->ind_queue);
		if (op && op->len <= chan->mtu)
			return queue_pop_head(att->ind_queue);
	}

	return NULL;
}
