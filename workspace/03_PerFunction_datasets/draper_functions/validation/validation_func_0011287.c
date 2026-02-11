show_warn(const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    fprintf(stderr, "warn: ");
    vfprintf(stderr, fmt, args);

    if (globals.options.backend) fprintf(stderr, "\n");
    va_end (args);
}
