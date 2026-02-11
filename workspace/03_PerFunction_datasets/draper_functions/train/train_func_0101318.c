gst_tcp_client_sink_start (GstTCPClientSink * this)
{
  int ret;
  gchar *ip;

  if (GST_OBJECT_FLAG_IS_SET (this, GST_TCP_CLIENT_SINK_OPEN))
    return TRUE;


  this->caps_sent = FALSE;


  GST_DEBUG_OBJECT (this, "opening sending client socket to %s:%d", this->host,
      this->port);
  if ((this->sock_fd.fd = socket (AF_INET, SOCK_STREAM, 0)) == -1) {
    GST_ELEMENT_ERROR (this, RESOURCE, OPEN_WRITE, (NULL), GST_ERROR_SYSTEM);
    return FALSE;
  }
  GST_DEBUG_OBJECT (this, "opened sending client socket with fd %d",
      this->sock_fd.fd);


  ip = gst_tcp_host_to_ip (GST_ELEMENT (this), this->host);
  if (!ip) {
    gst_tcp_socket_close (&this->sock_fd);
    return FALSE;
  }
  GST_DEBUG_OBJECT (this, "IP address for host %s is %s", this->host, ip);


  memset (&this->server_sin, 0, sizeof (this->server_sin));
  this->server_sin.sin_family = AF_INET;
  this->server_sin.sin_port = htons (this->port);
  this->server_sin.sin_addr.s_addr = inet_addr (ip);
  g_free (ip);

  GST_DEBUG_OBJECT (this, "connecting to server");
  ret = connect (this->sock_fd.fd, (struct sockaddr *) &this->server_sin,
      sizeof (this->server_sin));

  if (ret) {
    gst_tcp_socket_close (&this->sock_fd);
    switch (errno) {
      case ECONNREFUSED:
        GST_ELEMENT_ERROR (this, RESOURCE, OPEN_WRITE,
            (_("Connection to %s:%d refused."), this->host, this->port),
            (NULL));
        return FALSE;
        break;
      default:
        GST_ELEMENT_ERROR (this, RESOURCE, OPEN_READ, (NULL),
            ("connect to %s:%d failed: %s", this->host, this->port,
                g_strerror (errno)));
        return FALSE;
        break;
    }
  }

  GST_OBJECT_FLAG_SET (this, GST_TCP_CLIENT_SINK_OPEN);

  this->data_written = 0;

  return TRUE;
}
