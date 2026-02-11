pg_freeaddrinfo_all(int hint_ai_family, struct addrinfo * ai)
{
#ifdef HAVE_UNIX_SOCKETS
	if (hint_ai_family == AF_UNIX)
	{

		while (ai != NULL)
		{
			struct addrinfo *p = ai;

			ai = ai->ai_next;
			free(p->ai_addr);
			free(p);
		}
	}
	else
#endif
	{

		if (ai != NULL)
			freeaddrinfo(ai);
	}
}
