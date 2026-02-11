fmt_event(time_t seconds, unsigned int milli, unsigned long serial, const char *host)
{
    static char buf1[200], buf2[200];
    char fmt[] = "%a %b %d %H:%M:%S.%%ld %Y serial=%%ld host=%%s";
    struct tm *tmp;

    tmp = localtime(&seconds);
    if (tmp == NULL) {
        sprintf(buf2, "localtime error");
        return buf2;
    }

    if (strftime(buf1, sizeof(buf1), fmt, tmp) == 0) {
        sprintf(buf2, "strftime returned 0");
        return buf2;
    }

    snprintf(buf2, sizeof(buf2), buf1, milli, serial, host, sizeof(buf2));
    return buf2;
}
