rec_permissions_undo_func (NemoFileUndoInfo *info,
			   GtkWindow *parent_window)
{
	NemoFileUndoInfoRecPermissions *self = NEMO_FILE_UNDO_INFO_REC_PERMISSIONS (info);


	nemo_file_undo_manager_pop_flag ();

	if (g_hash_table_size (self->priv->original_permissions) > 0) {
		GList *gfiles_list;
		guint32 perm;
		GList *l;
		GFile *dest;
		char *item;

		gfiles_list = g_hash_table_get_keys (self->priv->original_permissions);
		for (l = gfiles_list; l != NULL; l = l->next) {
			item = l->data;
			perm = GPOINTER_TO_UINT (g_hash_table_lookup (self->priv->original_permissions, item));
			dest = g_file_new_for_uri (item);
			g_file_set_attribute_uint32 (dest,
						     G_FILE_ATTRIBUTE_UNIX_MODE,
						     perm, G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, NULL);
			g_object_unref (dest);
		}

		g_list_free (gfiles_list);

		file_undo_info_transfer_callback (NULL, TRUE, self);
	}
}
