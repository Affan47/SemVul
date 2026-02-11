camel_index_find (CamelIndex *idx,
                  const gchar *word)
{
	CamelIndexClass *class;
	CamelIndexCursor *ret;
	gchar *b = (gchar *) word;

	g_return_val_if_fail (CAMEL_IS_INDEX (idx), NULL);

	class = CAMEL_INDEX_GET_CLASS (idx);
	g_return_val_if_fail (class->find != NULL, NULL);

	if ((idx->state & CAMEL_INDEX_DELETED) != 0)
		return NULL;

	if (idx->normalize)
		b = idx->normalize (idx, word, idx->normalize_data);

	ret = class->find (idx, b);

	if (b != word)
		g_free (b);

	return ret;
}
