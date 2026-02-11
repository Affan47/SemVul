do_ipv6_test (void)
{
	SoupServer *ipv6_server;
	SoupURI *ipv6_uri;
	SoupAddress *ipv6_addr;
	SoupSession *session;
	SoupMessage *msg;

	debug_printf (1, "\nIPv6 server test\n");

	ipv6_addr = soup_address_new ("::1", SOUP_ADDRESS_ANY_PORT);
	soup_address_resolve_sync (ipv6_addr, NULL);
	ipv6_server = soup_server_new (SOUP_SERVER_INTERFACE, ipv6_addr,
				       NULL);
	g_object_unref (ipv6_addr);
	if (!ipv6_server) {
		debug_printf (1, "  skipping due to lack of IPv6 support\n");
		return;
	}

	soup_server_add_handler (ipv6_server, NULL, ipv6_server_callback, NULL, NULL);
	soup_server_run_async (ipv6_server);

	ipv6_uri = soup_uri_new ("http://[::1]/");
	soup_uri_set_port (ipv6_uri, soup_server_get_port (ipv6_server));

	session = soup_test_session_new (SOUP_TYPE_SESSION_ASYNC, NULL);

	debug_printf (1, "  HTTP/1.1\n");
	msg = soup_message_new_from_uri ("GET", ipv6_uri);
	soup_session_send_message (session, msg);
	if (!SOUP_STATUS_IS_SUCCESSFUL (msg->status_code)) {
		debug_printf (1, "    request failed: %d %s\n",
			      msg->status_code, msg->reason_phrase);
		errors++;
	}
	g_object_unref (msg);

	debug_printf (1, "  HTTP/1.0\n");
	msg = soup_message_new_from_uri ("GET", ipv6_uri);
	soup_message_set_http_version (msg, SOUP_HTTP_1_0);
	soup_session_send_message (session, msg);
	if (!SOUP_STATUS_IS_SUCCESSFUL (msg->status_code)) {
		debug_printf (1, "    request failed: %d %s\n",
			      msg->status_code, msg->reason_phrase);
		errors++;
	}
	g_object_unref (msg);

	soup_uri_free (ipv6_uri);
	soup_test_session_abort_unref (session);
	soup_test_server_quit_unref (ipv6_server);
}
