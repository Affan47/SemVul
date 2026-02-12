p11_rpc_message_write_attribute_buffer (p11_rpc_message *msg,
                                        CK_ATTRIBUTE_PTR arr,
                                        CK_ULONG num)
{
	CK_ATTRIBUTE_PTR attr;
	CK_ULONG i;

	assert (num == 0 || arr != NULL);
	assert (msg != NULL);
	assert (msg->output != NULL);


	assert (!msg->signature || p11_rpc_message_verify_part (msg, "fA"));


	p11_rpc_buffer_add_uint32 (msg->output, num);

	for (i = 0; i < num; ++i) {
		attr = &(arr[i]);


		p11_rpc_buffer_add_uint32 (msg->output, attr->type);


		p11_rpc_buffer_add_uint32 (msg->output, attr->pValue ? attr->ulValueLen : 0);
	}

	return !p11_buffer_failed (msg->output);
}
