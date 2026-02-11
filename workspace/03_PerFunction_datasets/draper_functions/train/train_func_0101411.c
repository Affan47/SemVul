Warning(const char *format, ...) {
    if (PbrtOptions.quiet) return;
    va_list args;
    va_start(args, format);
    processError(format, args, "Warning", PBRT_ERROR_CONTINUE);
    va_end(args);
}
