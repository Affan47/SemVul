download_socket_connected(gnutella_socket_t *s, void *owner)
{
	struct download *d = owner;

	download_check(d);
	g_assert(s == d->socket);

	download_connected(d);
}
