replace_rich_base_with_plain (GOStringRichImpl *rich)
{
	GOStringImpl *res = go_string_impl_new (rich->base.base.str, rich->base.hash,
		(rich->base.flags & (~GO_STRING_IS_RICH)) | GO_STRING_IS_SHARED, 2);

	rich->base.flags |= GO_STRING_IS_DEPENDENT;
	if ((rich->base.flags & GO_STRING_IS_SHARED)) {
		GSList *shares = g_hash_table_lookup (go_strings_shared, res->base.str);
		unsigned n = g_slist_length (shares);
		g_assert (rich->base.ref_count >= n);
		rich->base.flags &= ~GO_STRING_IS_SHARED;
		rich->base.ref_count -= n;
		res->ref_count += n;
		if (rich->base.ref_count == 0) {
			rich->base.ref_count = 1;
			go_string_unref ((GOString *) rich);
		} else {
			shares = g_slist_prepend (shares, rich);
			g_hash_table_replace (go_strings_shared,
			                      (gpointer) res->base.str, shares);
			n++;
		}
		if (n == 0)
			res->flags &= ~GO_STRING_IS_SHARED;
	} else
		g_hash_table_insert (go_strings_shared, (gpointer) res->base.str,
			g_slist_prepend (NULL, rich));

	return &res->base;
}
