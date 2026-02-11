start_opening_handshake (EvdWebsocketClient *self, EvdHttpConnection *conn)
{
  EvdHttpRequest *request;
  ConnectionData *data;

  data = g_object_get_data (G_OBJECT (conn), CONN_DATA_KEY);
  g_assert (data != NULL);

  request =
    evd_websocket_protocol_create_handshake_request (data->address,
                                                     NULL,
                                                     NULL,
                                                     &data->handshake_key);

  evd_http_connection_write_request_headers (conn,
                                             request,
                                             data->cancellable,
                                             on_handshake_sent,
                                             data);
  g_object_unref (request);
}
