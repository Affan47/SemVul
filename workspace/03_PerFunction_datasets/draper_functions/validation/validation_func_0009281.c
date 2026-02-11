git_transport_new(git_transport **out, const char *url)
{
	git_transport_cb fn;
	git_transport *transport;
	void *param;
	int error;

	if (transport_find_fn(url, &fn, &param) < 0) {
		giterr_set(GITERR_NET, "Unsupported URL protocol");
		return -1;
	}

	error = fn(&transport, param);
	if (error < 0)
		return error;

	*out = transport;

	return 0;
}
