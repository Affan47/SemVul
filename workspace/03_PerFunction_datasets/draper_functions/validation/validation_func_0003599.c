e_book_query_any_field_contains (const gchar *value)
{
	EBookQuery *ret = g_new0 (EBookQuery, 1);

	ret->type = E_BOOK_QUERY_TYPE_ANY_FIELD_CONTAINS;
	ret->query.any_field_contains.value = g_strdup (value);

	return ret;
}
