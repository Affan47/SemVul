miniwget(const char * url, int * size)
{
	unsigned short port;
	char * path;

	char hostname[MAXHOSTNAMELEN+1];
	*size = 0;
	if(!parseURL(url, hostname, &port, &path))
		return NULL;
	return miniwget2(url, hostname, port, path, size, 0, 0);
}
