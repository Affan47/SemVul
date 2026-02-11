store_initable_init (GInitable *initable,
                     GCancellable *cancellable,
                     GError **error)
{
	CamelStore *store;
	CamelService *service;
	const gchar *user_dir;
	gchar *filename;

	store = CAMEL_STORE (initable);


	if (!parent_initable_interface->init (initable, cancellable, error))
		return FALSE;

	service = CAMEL_SERVICE (initable);
	if ((store->flags & CAMEL_STORE_USE_CACHE_DIR) != 0)
		user_dir = camel_service_get_user_cache_dir (service);
	else
		user_dir = camel_service_get_user_data_dir (service);

	if (g_mkdir_with_parents (user_dir, S_IRWXU) == -1) {
		g_set_error_literal (
			error, G_FILE_ERROR,
			g_file_error_from_errno (errno),
			g_strerror (errno));
		return FALSE;
	}


	filename = g_build_filename (user_dir, CAMEL_DB_FILE, NULL);
	store->cdb_r = camel_db_open (filename, error);
	g_free (filename);

	if (store->cdb_r == NULL)
		return FALSE;

	if (camel_db_create_folders_table (store->cdb_r, error))
		return FALSE;


	store->cdb_w = store->cdb_r;

	return TRUE;
}
