static void handle_notify(struct bt_att_chan *chan, uint8_t *pdu,
							ssize_t pdu_len)
{
	struct bt_att *att = chan->att;
	const struct queue_entry *entry;
	bool found;
	uint8_t opcode = pdu[0];

	bt_att_ref(att);

	found = false;
	entry = queue_get_entries(att->notify_list);

	while (entry) {
		struct att_notify *notify = entry->data;

		entry = entry->next;

		if (!opcode_match(notify->opcode, opcode))
			continue;

		if ((opcode & ATT_OP_SIGNED_MASK) && att->crypto) {
			if (!handle_signed(att, pdu, pdu_len))
				return;
			pdu_len -= BT_ATT_SIGNATURE_LEN;
		}


		if (bt_att_get_link_type(att) == BT_ATT_BREDR) {
			switch (opcode) {
			case BT_ATT_OP_MTU_REQ:
				goto not_supported;
			}
		}

		found = true;

		if (notify->callback)
			notify->callback(chan, opcode, pdu + 1, pdu_len - 1,
							notify->user_data);


		if (queue_isempty(att->notify_list))
			break;
	}

not_supported:


	if (!found && get_op_type(opcode) != ATT_OP_TYPE_CMD)
		respond_not_supported(att, opcode);

	bt_att_unref(att);
}
