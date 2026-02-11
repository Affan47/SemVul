siginfo(sig)
	int sig;
{
	int i;
	time_t timenow;

	time(&timenow);

	for (i = 0; i < negc; ++i)
		if (!negv[i].allocated)
			continue;
		else {
			char srcstring[MAXSOCKSHOSTSTRING];

			slog(LOG_INFO, "%s: negotiating for %.0fs",
			sockshost2string(&negv[i].negstate.src, srcstring, sizeof(srcstring)),
			difftime(timenow, negv[i].state.time.negotiate_start));
		}
}
