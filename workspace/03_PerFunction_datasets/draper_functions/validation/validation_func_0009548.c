pk_backend_build_library_path (PkBackend *backend, const gchar *name)
{
	gchar *path;
	gchar *filename;
#if PK_BUILD_LOCAL
	const gchar *directory;
#endif
	g_return_val_if_fail (PK_IS_BACKEND (backend), NULL);
	g_return_val_if_fail (name != NULL, NULL);

	filename = g_strdup_printf ("libpk_backend_%s.so", name);
#if PK_BUILD_LOCAL

	directory = name;
	if (g_str_has_prefix (name, "test_"))
		directory = "test";


	path = g_build_filename ("..", "backends", directory, ".libs", filename, NULL);
	if (g_file_test (path, G_FILE_TEST_EXISTS) == FALSE) {
		g_debug ("local backend not found '%s'", path);
		g_free (path);
		path = g_build_filename (LIBDIR, "packagekit-backend", filename, NULL);
	}
#else
	path = g_build_filename (LIBDIR, "packagekit-backend", filename, NULL);
#endif
	g_free (filename);
	g_debug ("dlopening '%s'", path);

	return path;
}
