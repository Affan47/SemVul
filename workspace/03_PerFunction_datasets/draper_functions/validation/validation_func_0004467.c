rename_traverse_fi (CamelStore *store,
                    CamelStoreClass *store_class,
                    CamelFolderInfo *fi,
                    const gchar *old_full_name_prefix,
                    const gchar *new_full_name_prefix,
                    GCancellable *cancellable,
                    GError **error)
{
	gint old_prefix_len = strlen (old_full_name_prefix);
	gboolean ret = TRUE;

	while (fi && ret) {
		if (fi->full_name && g_str_has_prefix (fi->full_name, old_full_name_prefix)) {
			gchar *new_full_name, *old_dir, *new_dir;

			new_full_name = g_strconcat (new_full_name_prefix, fi->full_name + old_prefix_len, NULL);
			old_dir = maildir_full_name_to_dir_name (fi->full_name);
			new_dir = maildir_full_name_to_dir_name (new_full_name);


			ret = store_class->rename_folder_sync (store, old_dir, new_dir, cancellable, error);

			g_free (old_dir);
			g_free (new_dir);
			g_free (new_full_name);
		}

		if (fi->child && !rename_traverse_fi (store, store_class, fi->child, old_full_name_prefix, new_full_name_prefix, cancellable, error))
			return FALSE;

		fi = fi->next;
	}

	return ret;
}
