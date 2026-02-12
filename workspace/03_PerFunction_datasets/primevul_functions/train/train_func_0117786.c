pk_transaction_files_cb (PkBackendJob *job,
			 PkFiles *item,
			 PkTransaction *transaction)
{
	guint i;
	g_autofree gchar *package_id = NULL;
	g_auto(GStrv) files = NULL;

	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);


	g_object_get (item,
		      "package-id", &package_id,
		      "files", &files,
		      NULL);


	if (transaction->priv->role == PK_ROLE_ENUM_DOWNLOAD_PACKAGES &&
	    transaction->priv->cached_directory != NULL) {
		for (i = 0; files[i] != NULL; i++) {
			if (!g_str_has_prefix (files[i], transaction->priv->cached_directory)) {
				g_warning ("%s does not have the correct prefix (%s)",
					   files[i],
					   transaction->priv->cached_directory);
			}
		}
	}


	pk_results_add_files (transaction->priv->results, item);


	g_debug ("emitting files %s", package_id);
	g_dbus_connection_emit_signal (transaction->priv->connection,
				       NULL,
				       transaction->priv->tid,
				       PK_DBUS_INTERFACE_TRANSACTION,
				       "Files",
				       g_variant_new ("(s^as)",
						      package_id != NULL ? package_id : "",
						      files),
				       NULL);
}
