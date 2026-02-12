mwifiex_cmd_append_generic_ie(struct mwifiex_private *priv, u8 **buffer)
{
	int ret_len = 0;
	struct mwifiex_ie_types_header ie_header;


	if (!buffer)
		return 0;
	if (!(*buffer))
		return 0;


	if (priv->gen_ie_buf_len) {
		mwifiex_dbg(priv->adapter, INFO,
			    "info: %s: append generic ie len %d to %p\n",
			    __func__, priv->gen_ie_buf_len, *buffer);


		ie_header.type = cpu_to_le16(TLV_TYPE_PASSTHROUGH);
		ie_header.len = cpu_to_le16(priv->gen_ie_buf_len);
		memcpy(*buffer, &ie_header, sizeof(ie_header));


		*buffer += sizeof(ie_header);
		ret_len += sizeof(ie_header);


		memcpy(*buffer, priv->gen_ie_buf, priv->gen_ie_buf_len);


		*buffer += priv->gen_ie_buf_len;
		ret_len += priv->gen_ie_buf_len;


		priv->gen_ie_buf_len = 0;
	}


	return ret_len;
}
