hpi_stream_host_buffer_detach(u32  h_stream)
{
	struct hpi_message hm;
	struct hpi_response hr;
	unsigned int obj = hpi_handle_object(h_stream);

	if (!h_stream)
		return HPI_ERROR_INVALID_OBJ;

	hpi_init_message_response(&hm, &hr,  obj,
			obj == HPI_OBJ_OSTREAM ?
				HPI_OSTREAM_HOSTBUFFER_FREE :
				HPI_ISTREAM_HOSTBUFFER_FREE);

	hpi_handle_to_indexes(h_stream, &hm.adapter_index,
				&hm.obj_index);
	hm.u.d.u.buffer.command = HPI_BUFFER_CMD_INTERNAL_REVOKEADAPTER;
	hpi_send_recv(&hm, &hr);
	return hr.error;
}
