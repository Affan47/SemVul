signame(int sig)
{
	static char sigbuf[20];

	switch (sig)
	{
	case SIGINT:
		sprintf(sigbuf, "SIGINT-%d", pc->sigint_cnt+1);
		return sigbuf;
	case SIGPIPE:
		return "SIGPIPE";
	case SIGSEGV:
		return "SIGSEGV";
	default:
		sprintf(sigbuf, "%d", sig);
		return sigbuf;
	}
}
