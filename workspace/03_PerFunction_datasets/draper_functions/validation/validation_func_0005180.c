apiversion(struct io_data *io_data, __maybe_unused SOCKETTYPE c, __maybe_unused char *param, bool isjson, __maybe_unused char group)
{
	struct api_data *root = NULL;
	char buf[TMPBUFSIZ];
	bool io_open;

	message(io_data, MSG_VERSION, 0, NULL, isjson);
	io_open = io_add(io_data, isjson ? COMSTR JSON_VERSION : _VERSION COMSTR);

	root = api_add_string(root, "CGMiner", VERSION, false);
	root = api_add_const(root, "API", APIVERSION, false);

	root = print_data(root, buf, isjson, false);
	io_add(io_data, buf);
	if (isjson && io_open)
		io_close(io_data);
}
