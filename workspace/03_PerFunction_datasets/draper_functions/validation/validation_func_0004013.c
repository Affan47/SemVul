camel_text_index_remove (const gchar *old)
{
	gchar *block, *key;
	gsize block_len, key_len;
	gint ret = 0;


	block_len = strlen (old) + 12;
	block = alloca (block_len);
	key_len = strlen (old) + 12;
	key = alloca (key_len);
	g_snprintf (block, block_len, "%s.index", old);
	g_snprintf (key, key_len, "%s.index.data", old);

	if (g_unlink (block) == -1 && errno != ENOENT && errno != ENOTDIR)
		ret = -1;
	if (g_unlink (key) == -1 && errno != ENOENT && errno != ENOTDIR)
		ret = -1;

	if (ret == 0)
		errno = 0;

	return ret;
}
