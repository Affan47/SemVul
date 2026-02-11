test_default_database_is_singleton (void)
{
  GTlsBackend *backend;
  GTlsDatabase *database;
  GTlsDatabase *check;

  backend = g_tls_backend_get_default ();
  g_assert (G_IS_TLS_BACKEND (backend));

  database = g_tls_backend_get_default_database (backend);
  g_assert (G_IS_TLS_DATABASE (database));

  check = g_tls_backend_get_default_database (backend);
  g_assert (database == check);

  g_object_unref (database);
  g_object_unref (check);
}
