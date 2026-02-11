chirp_fs_chirp_init(const char *url)
{
	char *h, *p;
	const char *path;


	h = strchr(url, '/');


	while(*h == '/')
		h++;
	if(!h)
		return 0;


	p = strchr(h, '/');
	if(p) {
		path = strdup(p);
	} else {
		path = "/";
	}

	chirp_fs_chirp_hostport = strdup(h);

	p = strchr(chirp_fs_chirp_hostport, '/');
	if(p)
		*p = 0;

	debug(D_CHIRP, "url: %s", url);

	return path;
}
