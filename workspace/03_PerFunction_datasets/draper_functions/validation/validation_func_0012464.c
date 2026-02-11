test_basic_connection (TestConnection *test,
                       gconstpointer   data)
{
  GIOStream *connection;
  GError *error = NULL;

  connection = start_async_server_and_connect_to_it (test, G_TLS_AUTHENTICATION_NONE, TRUE);
  test->client_connection = g_tls_client_connection_new (connection, test->identity, &error);
  g_assert_no_error (error);
  g_object_unref (connection);


  g_tls_client_connection_set_validation_flags (G_TLS_CLIENT_CONNECTION (test->client_connection),
                                                0);

  read_test_data_async (test);
  g_main_loop_run (test->loop);

  g_assert_no_error (test->read_error);
  g_assert_no_error (test->server_error);
}
