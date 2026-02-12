sigint_handler(int sig)
{

	signal(SIGINT, sigint_handler);

	dlog(LOG_DEBUG, 4, "sigint_handler called");

	++sigint_received;

	if(sigint_received > 1){
		dlog(LOG_ERR, 1, "sigint_handler called %d times...aborting...", sigint_received);
		abort();
	}
}
