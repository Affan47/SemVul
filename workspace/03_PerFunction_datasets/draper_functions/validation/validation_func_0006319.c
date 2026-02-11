tia_open_device(struct devmodule* dev, const char* optv[])
{
	struct tia_eegdev* tdev = get_tia(dev);
	unsigned short port = atoi(optv[OPT_PORT]);
	const char *url = optv[OPT_HOST];
	size_t hostlen = url ? strlen(url) : 0;
	char hoststring[hostlen + 1];
	char* host = url ? hoststring : NULL;

	tdev->datafd = tdev->ctrlfd = -1;

	if ( (url && parse_url(url, host, &port))
	  || init_xml_parser(tdev)
	  || init_ctrl_com(tdev, host, port)
	  || setup_device_config(tdev, url)
	  || init_data_com(tdev, host) ) {
		tia_close_device(dev);
		return -1;
	}
	return 0;
}
