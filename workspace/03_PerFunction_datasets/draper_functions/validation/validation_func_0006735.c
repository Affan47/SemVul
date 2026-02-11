sdp_gen_record_pdu(const sdp_record_t *rec, sdp_buf_t *buf)
{
	memset(buf, 0, sizeof(sdp_buf_t));
	sdp_list_foreach(rec->attrlist, sdp_attr_size, buf);

	buf->data = malloc(buf->buf_size);
	if (!buf->data)
		return -ENOMEM;
	buf->data_size = 0;
	memset(buf->data, 0, buf->buf_size);

	sdp_list_foreach(rec->attrlist, sdp_attr_pdu, buf);

	return 0;
}
