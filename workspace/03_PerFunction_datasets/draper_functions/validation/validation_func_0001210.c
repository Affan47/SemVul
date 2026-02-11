isns_simple_call(isns_socket_t *sock, isns_simple_t **inout)
{
	isns_simple_t	*simp = *inout;
	isns_message_t	*msg, *resp;
	int		status;

	isns_simple_print(simp, isns_debug_message);

	status = isns_simple_encode(simp, &msg);
	if (status != ISNS_SUCCESS) {
		isns_error("Unable to encode %s: %s\n",
				isns_function_name(simp->is_function),
				isns_strerror(status));
		return status;
	}

	isns_debug_message("Sending request, len=%d\n",
			buf_avail(msg->im_payload));

	resp = isns_socket_call(sock, msg,
			isns_config.ic_network.call_timeout);
	isns_assert(msg->im_users == 1);
	isns_message_release(msg);

	if (resp == NULL) {
		isns_error("Timed out while waiting for reply\n");
		return ISNS_INTERNAL_ERROR;
	}

	isns_debug_message("Received reply, len=%d\n",
			buf_avail(resp->im_payload));
	isns_assert(resp->im_users == 1);

	status = isns_message_status(resp);
	if (status != ISNS_SUCCESS) {
		isns_message_release(resp);
		return status;
	}

	status = isns_simple_decode(resp, &simp);
	isns_message_release(resp);

	if (status) {
		isns_error("Unable to decode server response: %s (status 0x%04x)\n",
				isns_strerror(status), status);
		return status;
	}

	isns_simple_print(simp, isns_debug_message);

	isns_simple_free(*inout);
	*inout = simp;
	return ISNS_SUCCESS;
}
