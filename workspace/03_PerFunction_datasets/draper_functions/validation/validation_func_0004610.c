limit_mem_usage(unsigned long rss,
		unsigned long as)
{
    int n;
    struct rlimit lim;

#ifdef RLIMIT_RSS
    if (rss) {

	rss *= 1024;
	lim.rlim_cur = rss;
	lim.rlim_max = rss;
	n = setrlimit(RLIMIT_RSS, &lim);
	if (n < 0) {
	    syslog(LOG_WARNING, "setrlimit(RLIMIT_RSS, %lu) failed: %m",
		   rss);
	}
    }
#endif
    if (as) {

	as *= 1024;
	lim.rlim_cur = as;
	lim.rlim_max = as;
#ifdef RLIMIT_AS
	n = setrlimit(RLIMIT_AS, &lim);
	if (n < 0) {
	    syslog(LOG_WARNING, "setrlimit(RLIMIT_AS, %lu) failed: %m",
		   as);
	}
#endif

#ifdef RLIMIT_DATA
	n = setrlimit(RLIMIT_DATA, &lim);
	if (n < 0) {
	    syslog(LOG_WARNING, "setrlimit(RLIMIT_DATA, %lu) failed: %m",
		   as);
	}
#endif

    }
}
