format(char *buf, int level, const char *place, int e,
		   const char *fmt, int with_timestamp)
{
    static char *tab[] = {
	"DEBUG: ",
	"INFO: ",
	"WARNING: ",
	"ERROR: ",
	"PANIC: ",
	"LOG: "
    };
    static int tab_size = sizeof(tab) / sizeof(tab[0]);
    time_t t;
    struct tm tm;
    char *p, prefix[1024];
    long tid, pid;

    p = prefix;

    if (with_timestamp) {
        time(&t);
#if LOG_TIMESTAMP_LOCALTIME
        tm = gw_localtime(t);
#else
        tm = gw_gmtime(t);
#endif
        sprintf(p, "%04d-%02d-%02d %02d:%02d:%02d ",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
        tm.tm_hour, tm.tm_min, tm.tm_sec);

        p = strchr(p, '\0');
    }

    gwthread_self_ids(&tid, &pid);
    sprintf(p, "[%ld] [%ld] ", pid, tid);

    p = strchr(p, '\0');
    if (level < 0 || level >= tab_size)
	sprintf(p, "UNKNOWN: ");
    else
	sprintf(p, "%s", tab[level]);

    p = strchr(p, '\0');
    if (place != NULL && *place != '\0')
	sprintf(p, "%s: ", place);

    if (strlen(prefix) + strlen(fmt) > FORMAT_SIZE / 2) {
	sprintf(buf, "%s <OUTPUT message too long>\n", prefix);
	return;
    }

    if (e == 0)
	sprintf(buf, "%s%s\n", prefix, fmt);
    else
	sprintf(buf, "%s%s\n%sSystem error %d: %s\n",
		prefix, fmt, prefix, e, strerror(e));
}
