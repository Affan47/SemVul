file_size(const char* const path, double& size) {
    int retval;

#if defined(_WIN32) && !defined(__CYGWIN32__) && !defined(__MINGW32__)
    struct __stat64 sbuf;
    retval = _stat64(path, &sbuf);
#else
    struct stat sbuf;
    retval = stat(path, &sbuf);
#endif
    if (retval) return ERR_NOT_FOUND;
    size = (double)sbuf.st_size;
    return 0;
}
