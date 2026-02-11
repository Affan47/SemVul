do_one_server_aliases_test (SoupURI    *uri,
			    const char *alias,
			    gboolean    succeed)
{
	GSocketClient *client;
	GSocketConnectable *addr;
	GSocketConnection *conn;
	GInputStream *in;
	GOutputStream *out;
	GError *error = NULL;
	GString *req;
	static char buf[1024];

	debug_printf (1, "  %s via %s\n", alias, uri->scheme);


	client = g_socket_client_new ();
	if (uri->scheme == SOUP_URI_SCHEME_HTTPS) {
		g_socket_client_set_tls (client, TRUE);
		g_socket_client_set_tls_validation_flags (client, 0);
	}
	addr = g_network_address_new (uri->host, uri->port);

	conn = g_socket_client_connect (client, addr, NULL, &error);
	g_object_unref (addr);
	g_object_unref (client);
	if (!conn) {
		debug_printf (1, "    error connecting to server: %s\n",
			      error->message);
		g_error_free (error);
		errors++;
		return;
	}

	in = g_io_stream_get_input_stream (G_IO_STREAM (conn));
	out = g_io_stream_get_output_stream (G_IO_STREAM (conn));

	req = g_string_new (NULL);
	g_string_append_printf (req, "GET %s://%s:%d HTTP/1.1\r\n",
				alias, uri->host, uri->port);
	g_string_append_printf (req, "Host: %s:%d\r\n",
				uri->host, uri->port);
	g_string_append (req, "Connection: close\r\n\r\n");

	if (!g_output_stream_write_all (out, req->str, req->len, NULL, NULL, &error)) {
		debug_printf (1, "    error sending request: %s\n",
			      error->message);
		g_error_free (error);
		errors++;
		g_object_unref (conn);
		g_string_free (req, TRUE);
		return;
	}
	g_string_free (req, TRUE);

	if (!g_input_stream_read_all (in, buf, sizeof (buf), NULL, NULL, &error)) {
		debug_printf (1, "    error reading response: %s\n",
			      error->message);
		g_error_free (error);
		errors++;
		g_object_unref (conn);
		return;
	}

	if ((succeed && !g_str_has_prefix (buf, "HTTP/1.1 200 ")) ||
	    (!succeed && !g_str_has_prefix (buf, "HTTP/1.1 400 "))) {
		debug_printf (1, "    unexpected response: %.*s\n",
			      (int) strcspn (buf, "\r\n"), buf);
		errors++;
	}

	g_io_stream_close (G_IO_STREAM (conn), NULL, NULL);
	g_object_unref (conn);
}
