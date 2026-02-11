msprintf(struct mstring *s, const char *fmt, ...)
{
static char	buf[4096];
va_list		args;
int		len;

    if (!s || !s->base) return;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);

    len = strlen(buf);
    if (len > (s->end - s->ptr)) {
	int	cp = s->ptr - s->base, cl = s->end - s->base, nl = cl;
	while (len > (nl - cp))
	    nl = nl + nl + TAIL;
	if ((s->base = realloc(s->base, nl))) {
	    s->ptr = s->base + cp;
	    s->end = s->base + nl; }
	else {
	    s->ptr = s->end = 0;
	    return; } }
    memcpy(s->ptr, buf, len);
    s->ptr += len;
}
