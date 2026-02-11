Rem(const char *ip, short port)
{
	char buf[64];
	snprintf(buf, sizeof(buf), "%s:%d", ip, port);

	if (Has(ip, port)) {
		inset_t::iterator f = inset.find(buf);
		if (f != inset.end()) {
			free((void *) *f);
			inset.erase(f);
		}
	}
}
