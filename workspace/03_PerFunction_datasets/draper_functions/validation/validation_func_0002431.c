hsc_msgs_alloc(struct hsc_channel *channel)
{
	struct hsi_msg *msg;
	int i;

	for (i = 0; i < HSC_MSGS; i++) {
		msg = hsc_msg_alloc(max_data_size);
		if (!msg)
			goto out;
		msg->channel = channel->ch;
		list_add_tail(&msg->link, &channel->free_msgs_list);
	}

	return 0;
out:
	hsc_free_list(&channel->free_msgs_list);

	return -ENOMEM;
}
