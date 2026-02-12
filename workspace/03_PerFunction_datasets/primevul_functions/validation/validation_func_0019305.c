mwifiex_cmd_append_wapi_ie(struct mwifiex_private *priv, u8 **buffer)
{
	int retLen = 0;
	struct mwifiex_ie_types_header ie_header;


	if (buffer == NULL)
		return 0;
	if (*buffer == NULL)
		return 0;


	if (priv->wapi_ie_len) {
		mwifiex_dbg(priv->adapter, CMD,
			    "cmd: append wapi ie %d to %p\n",
			    priv->wapi_ie_len, *buffer);


		ie_header.type = cpu_to_le16(TLV_TYPE_WAPI_IE);
		ie_header.len = cpu_to_le16(priv->wapi_ie_len);
		memcpy(*buffer, &ie_header, sizeof(ie_header));


		*buffer += sizeof(ie_header);
		retLen += sizeof(ie_header);


		memcpy(*buffer, priv->wapi_ie, priv->wapi_ie_len);


		*buffer += priv->wapi_ie_len;
		retLen += priv->wapi_ie_len;

	}

	return retLen;
}
