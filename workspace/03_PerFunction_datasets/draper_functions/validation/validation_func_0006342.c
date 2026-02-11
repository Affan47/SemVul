test_simultaneous_sync (TestConnection *test,
			gconstpointer   data)
{
  GIOStream *connection;
  GTlsCertificateFlags flags;
  GError *error = NULL;
  GThread *read_thread, *write_thread;

  connection = start_echo_server_and_connect_to_it (test);
  test->client_connection = g_tls_client_connection_new (connection, test->identity, &error);
  g_assert_no_error (error);
  g_object_unref (connection);

  flags = G_TLS_CERTIFICATE_VALIDATE_ALL &
    ~(G_TLS_CERTIFICATE_UNKNOWN_CA | G_TLS_CERTIFICATE_BAD_IDENTITY);
  g_tls_client_connection_set_validation_flags (G_TLS_CLIENT_CONNECTION (test->client_connection),
                                                flags);

  memset (test->buf, 0, sizeof (test->buf));
  test->nread = test->nwrote = 0;

  read_thread = g_thread_new ("reader", simul_read_thread, test);
  write_thread = g_thread_new ("writer", simul_write_thread, test);


  while (!test->server_connection)
    g_main_context_iteration (NULL, FALSE);

  g_thread_join (write_thread);
  g_thread_join (read_thread);

  g_assert_cmpint (test->nread, ==, TEST_DATA_LENGTH);
  g_assert_cmpint (test->nwrote, ==, TEST_DATA_LENGTH);
  g_assert_cmpstr (test->buf, ==, TEST_DATA);

  g_io_stream_close (test->client_connection, NULL, &error);
  g_assert_no_error (error);
}
