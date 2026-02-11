chirp_client_localpath(struct chirp_client * c, const char *path, char *localpath, int length, time_t stoptime)
{
	INT64_T result;
	INT64_T actual;

	char safepath[CHIRP_LINE_MAX];
	url_encode(path, safepath, sizeof(safepath));

	result = simple_command(c, stoptime, "localpath %s\n", path);

	if(result > 0) {
		actual = link_read(c->link, localpath, result, stoptime);
		if(actual != result) {
			c->broken = 1;
			errno = ECONNRESET;
			return -1;
		}
	}

	return result;
}
