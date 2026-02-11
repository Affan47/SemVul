xmms_bindata_client_retrieve (xmms_bindata_t *bindata, const gchar *hash,
                              xmms_error_t *err)
{
	xmmsv_t *res;
	gchar *path;
	GString *str;
	FILE *fp;

	path = xmms_bindata_build_path (bindata, hash);

	fp = fopen (path, "rb");
	if (!fp) {
		xmms_log_error ("Requesting '%s' which is not on the server", hash);
		xmms_error_set (err, XMMS_ERROR_NOENT, "File not found!");
		g_free (path);
		return NULL;
	}

	g_free (path);

	str = g_string_new (NULL);
	while (!feof (fp)) {
		gchar buf[1024];
		gint l;

		l = fread (buf, 1, 1024, fp);
		if (ferror (fp)) {
			g_string_free (str, TRUE);
			xmms_log_error ("Error reading bindata '%s'", hash);
			xmms_error_set (err, XMMS_ERROR_GENERIC, "Error reading file");
			fclose (fp);
			return NULL;
		}
		g_string_append_len (str, buf, l);
	}

	fclose (fp);

	res = xmmsv_new_bin ((unsigned char *)str->str, str->len);

	g_string_free (str, TRUE);

	return res;
}
