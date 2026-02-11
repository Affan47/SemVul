mprWriteToOsLog(cchar *message, int flags, int level)
{
    int     sflag;

    if (flags & MPR_FATAL_SRC) {
        sflag = LOG_ERR;

    } else if (flags & MPR_ASSERT_SRC) {
        sflag = LOG_WARNING;

    } else if (flags & MPR_ERROR_SRC) {
        sflag = LOG_ERR;

    } else {
        sflag = LOG_WARNING;
    }
    syslog(sflag, "%s", message);
}
