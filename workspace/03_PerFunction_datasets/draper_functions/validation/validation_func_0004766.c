camel_folder_change_info_add_update (CamelFolderChangeInfo *info,
                                     const gchar *uid)
{
	struct _CamelFolderChangeInfoPrivate *p;
	gchar *key;
	gint value;

	g_return_if_fail (info != NULL);
	g_return_if_fail (uid != NULL);

	p = info->priv;

	if (p->uid_source == NULL) {
		camel_folder_change_info_add_uid (info, uid);
		return;
	}

	if (g_hash_table_lookup_extended (p->uid_source, uid, (gpointer) &key, (gpointer) &value)) {
		g_hash_table_remove (p->uid_source, key);
	} else {
		camel_folder_change_info_add_uid (info, uid);
	}
}
