guid_to_str_buf(const e_guid_t *guid, gchar *buf, int buf_len)
{
	char *tempptr = buf;

	if (buf_len < GUID_STR_LEN) {
		g_strlcpy(buf, BUF_TOO_SMALL_ERR, buf_len);
		return buf;
	}


	tempptr    = dword_to_hex(tempptr, guid->data1);
	*tempptr++ = '-';
	tempptr    = word_to_hex(tempptr, guid->data2);
	*tempptr++ = '-';
	tempptr    = word_to_hex(tempptr, guid->data3);
	*tempptr++ = '-';
	tempptr    = bytes_to_hexstr(tempptr, &guid->data4[0], 2);
	*tempptr++ = '-';
	tempptr    = bytes_to_hexstr(tempptr, &guid->data4[2], 6);

	*tempptr   = '\0';
	return buf;
}
