ap_message_add_key(ap_message_t *msg, ap_key_t *key)
{
	if (!msg || !key)
		return;

	if (msg->root == NULL) {

		msg->root = key;
		msg->tail = msg->root;
		msg->current = msg->tail;
	} else {

		msg->tail->next = key;
		msg->tail = key;
	}
	msg->header.nr_keys++;

}
