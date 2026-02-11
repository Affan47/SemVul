GC_err_printf(format, a, b, c, d, e, f)
GC_CONST char * format;
long a, b, c, d, e, f;
{
    char buf[1025];

    buf[1024] = 0x15;
    (void) sprintf(buf, format, a, b, c, d, e, f);
    if (buf[1024] != 0x15) ABORT("GC_err_printf clobbered stack");
    if (WRITE(GC_stderr, buf, strlen(buf)) < 0) ABORT("write to stderr failed");
}
