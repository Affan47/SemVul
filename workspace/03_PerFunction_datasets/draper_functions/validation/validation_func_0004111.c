vlog(const char* fmt0, va_list ap)
{
   if (fd == -1)
	return;
    int oerrno = errno;
    char buf[1024];
    timeval tv;
    (void) gettimeofday(&tv, 0);
    strftime(buf, sizeof (buf), "%h %d %T", localtime((time_t*) &tv.tv_sec));
    fxStr s = buf | fxStr::format(".%02u: [%5d]: ", tv.tv_usec / 10000, pid);


    fxStackBuffer fmt;
    for (const char* fp = fmt0; *fp; fp++) {
	if (fp[0] == '%')
	    switch (fp[1]) {
	    case '%':
		fmt.put("%%"); fp++;
		continue;
	    case 'm':
		fmt.put(strerror(oerrno)), fp++;
		continue;
	    }
	fmt.put(fp[0]);
    }
    fmt.put('\n'); fmt.put('\0');
    s.append(fxStr::vformat((const char*) fmt, ap));
    (void) Sys::write(fd, (const char*)s, s.length());
}
