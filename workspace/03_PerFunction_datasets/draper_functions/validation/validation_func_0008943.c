convdate(const char *date, char mode)
{
    time_t seconds;


    if (date == NULL) {
        seconds = time(NULL);
    } else if (mode == 'c') {
        if (!isdigits(date)) {
            warn("\"%s\" doesn't look like a number", date);
            return false;
        } else {
            seconds = (time_t) atol(date);
        }
    } else {
        seconds = parsedate_rfc5322_lax(date);
        if (seconds == (time_t) -1) {
            warn("can't convert \"%s\"", date);
            return false;
        }
    }


    if (mode == 'n') {
        printf("%ld\n", (long) seconds);
        return true;
    } else {
        return print_date(seconds);
    }
}
