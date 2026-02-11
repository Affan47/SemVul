test_file_database_handle (TestFileDatabase *test,
                           gconstpointer     unused)
{
  GTlsCertificate *certificate;
  GTlsCertificate *check;
  GError *error = NULL;
  gchar *handle;


  certificate = g_tls_certificate_new_from_file (tls_test_file_path ("ca.pem"), &error);
  g_assert_no_error (error);
  g_assert (G_IS_TLS_CERTIFICATE (certificate));

  handle = g_tls_database_create_certificate_handle (test->database, certificate);
  g_assert (handle != NULL);
  g_assert (g_str_has_prefix (handle, "file:///"));

  check = g_tls_database_lookup_certificate_for_handle (test->database, handle,
                                                        NULL, G_TLS_DATABASE_LOOKUP_NONE,
                                                        NULL, &error);
  g_assert_no_error (error);
  g_assert (G_IS_TLS_CERTIFICATE (check));

  g_free (handle);
  g_object_unref (check);
  g_object_unref (certificate);
}
