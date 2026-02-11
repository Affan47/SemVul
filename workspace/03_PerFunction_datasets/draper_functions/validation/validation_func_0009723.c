main(int argc, char **argv)
{
	struct timeval tv;
	int i;
#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	(void) WSAStartup(wVersionRequested, &wsaData);
#endif

	evutil_weakrand_seed_(&weakrand_state, 0);


	event_init();

	for (i = 0; i < NEVENT; i++) {
		ev[i] = malloc(sizeof(struct event));


		evtimer_set(ev[i], time_cb, ev[i]);
		tv.tv_sec = 0;
		tv.tv_usec = rand_int(50000);
		evtimer_add(ev[i], &tv);
	}

	event_dispatch();

	return (called < NEVENT);
}
