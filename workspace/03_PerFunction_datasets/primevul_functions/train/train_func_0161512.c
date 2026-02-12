endTimer(char *format, ...)
{


#ifdef HAVE_STDARG_H
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fprintf(stderr, " was not timed\n");
#else


#endif
}
