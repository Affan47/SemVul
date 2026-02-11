trace_printf(const char *s, ...)
{
    va_list         ap;
    char	    buffer[3000];

    va_start(ap, s);
    vsnprintf(buffer, sizeof(buffer), s, ap);
    va_end(ap);
    for (s = buffer; *s; ++s)
	trace_putchar(*s);
}
