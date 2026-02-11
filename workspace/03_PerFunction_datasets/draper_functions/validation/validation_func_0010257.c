socket_str2addr(char *name, u_int32_t dflt)
{
	struct hostent *hptr;
	struct in_addr iadr;

#if defined(COMPILE_DEBUG)
	debug(3, "str2addr: in='%.1024s'", NIL(name));
#endif

	if (name == NULL)
		return dflt;
	memset(&iadr, 0, sizeof(iadr));


	if (*name >= '0' && *name <= '9') {
		if (inet_aton(name, &iadr) == 0)
			return dflt;
		return ntohl(iadr.s_addr);
	}


	if ((hptr = gethostbyname(name)) != NULL) {
		memcpy(&iadr.s_addr, hptr->h_addr, sizeof(iadr.s_addr));
		return (u_int32_t) ntohl(iadr.s_addr);
	}


	return dflt;
}
