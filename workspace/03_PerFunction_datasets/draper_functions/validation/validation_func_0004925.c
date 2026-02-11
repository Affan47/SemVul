vlog_prio(int prio, const char *fmt, va_list ap)
{
        char *str;

        if (asprintf(&str, "pid=%d: %s", mypid, fmt) != -1) {
                vsyslog(LOG_DAEMON | prio, str, ap);
                free(str);
        }
}
