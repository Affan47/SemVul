xmms_ipc_hostname (const char *path)
{
	xmms_url_t *url;
	char* ret = NULL;

	url = parse_url (path);
	if (!strcasecmp (url->protocol, "tcp")) {
		if (strlen (url->host)) {
			ret = strdup (url->host);
		}
	}
	free_url (url);

	return ret;
}
