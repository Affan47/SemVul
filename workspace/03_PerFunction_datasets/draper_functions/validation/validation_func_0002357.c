start_wapbox(void) {
	int wap_socket;
	int wapbox;

	wap_socket = make_server_socket(wapbox_port, NULL);
	if (wap_socket < 0)
		panic(0, "Couldn't make wapbox port\n");

	wapbox = accept(wap_socket, NULL, NULL);
	if (wapbox < 0)
		panic(errno, "Wapbox could not connect\n");

	close(wap_socket);

	return conn_wrap_fd(wapbox, 0);
}
