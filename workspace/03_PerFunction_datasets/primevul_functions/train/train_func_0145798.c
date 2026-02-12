bytestring_to_str(wmem_allocator_t *scope, const guint8 *ad, const guint32 len, const char punct)
{
	gchar *buf;
	guint32 buflen = len;
	gchar *buf_ptr;
	int truncated = 0;

	if (len == 0)
		return wmem_strdup(scope, "");

	if (!ad)
		REPORT_DISSECTOR_BUG("Null pointer passed to bytestring_to_str()");

	if (!punct)
		return bytes_to_str(scope, ad, len);

	buf=(gchar *)wmem_alloc(scope, MAX_BYTE_STR_LEN+3+1);
	if (buflen > MAX_BYTE_STR_LEN/3) {
		truncated = 1;
		buflen = MAX_BYTE_STR_LEN/3;
	}

	buf_ptr = bytes_to_hexstr_punct(buf, ad, buflen, punct);

	if (truncated) {
		*buf_ptr++ = punct;
		buf_ptr    = g_stpcpy(buf_ptr, UTF8_HORIZONTAL_ELLIPSIS);
	}

	*buf_ptr = '\0';
	return buf;
}
