gst_tcp_server_sink_socket_condition (GSocket * socket, GIOCondition condition,
    GstTCPServerSink * sink)
{
  if ((condition & G_IO_ERR)) {
    goto error;
  } else if ((condition & G_IO_IN) || (condition & G_IO_PRI)) {
    if (!gst_tcp_server_sink_handle_server_read (sink))
      return FALSE;
  }

  return TRUE;

error:
  GST_ELEMENT_ERROR (sink, RESOURCE, READ, (NULL),
      ("client connection failed"));

  return FALSE;
}
