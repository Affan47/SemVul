file_get_last_modified_string(const char* fn, const char* timeformat,
                                  anbool utc, char* output, size_t outsize) {
    struct tm tym;
	time_t t;

	t = file_get_last_modified_time(fn);
	if (t == 0) {
		return -1;
	}
    if (utc) {
        if (!gmtime_r(&t, &tym)) {
            SYSERROR("gmtime_r() failed");
            return -1;
        }
    } else {
        if (!localtime_r(&t, &tym)) {
            SYSERROR("localtime_r() failed");
            return -1;
        }
    }
    strftime(output, outsize, timeformat, &tym);
    return 0;
}
