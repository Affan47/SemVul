peer_closed (EvdTransport *transport,
             EvdPeer      *peer,
             gboolean      gracefully)
{
  gpointer peer_data;
  EvdHttpConnection *conn;
  ConnectionData *conn_data;

  peer_data = g_object_get_data (G_OBJECT (peer), PEER_DATA_KEY);
  if (peer_data == NULL)
    return;

  conn = EVD_HTTP_CONNECTION (peer_data);

  if (! g_io_stream_is_closed (G_IO_STREAM (conn)))
    {
      GError *error = NULL;
      guint16 code;


      code = gracefully ?
        EVD_WEBSOCKET_CLOSE_NORMAL :
        EVD_WEBSOCKET_CLOSE_ABNORMAL;

      if (! evd_websocket_protocol_close (conn, code, NULL, &error))
        {

          g_print ("Error closing websocket connection: %s\n", error->message);
          g_error_free (error);
        }
    }

  conn_data = g_object_get_data (G_OBJECT (conn), CONN_DATA_KEY);
  conn_data->peer = NULL;

  g_object_set_data (G_OBJECT (peer), PEER_DATA_KEY, NULL);
}
