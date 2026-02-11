x_asprintf(char **strp, const char *file, int line, const char *fmt, ...)
{
    va_list args, args_copy;
    int status;

    va_start(args, fmt);
    va_copy(args_copy, args);
    status = vasprintf(strp, fmt, args_copy);
    va_end(args_copy);
    while (status < 0) {
        va_copy(args_copy, args);
        status = vsnprintf(NULL, 0, fmt, args_copy);
        va_end(args_copy);
        (*xmalloc_error_handler)("asprintf", status + 1, file, line);
        va_copy(args_copy, args);
        status = vasprintf(strp, fmt, args_copy);
        va_end(args_copy);
    }
}
