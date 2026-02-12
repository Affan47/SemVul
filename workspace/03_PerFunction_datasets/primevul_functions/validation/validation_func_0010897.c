p11_rpc_message_write_ulong_array (p11_rpc_message *msg,
                                   CK_ULONG_PTR array,
                                   CK_ULONG n_array)
{
	CK_ULONG i;

	assert (msg != NULL);
	assert (msg->output != NULL);


	assert (!msg->signature || p11_rpc_message_verify_part (msg, "au"));


	p11_rpc_buffer_add_byte (msg->output, array ? 1 : 0);
	p11_rpc_buffer_add_uint32 (msg->output, n_array);


	if (array) {
		for (i = 0; i < n_array; ++i)
			p11_rpc_buffer_add_uint64 (msg->output, array[i]);
	}

	return !p11_buffer_failed (msg->output);
}
