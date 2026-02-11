env_setf(const char *name, const char *fmt, ...)
{
    char            buffer[1000];
    va_list         ap;

    va_start(ap, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, ap);
    va_end(ap);
    env_set(name, buffer);
}
