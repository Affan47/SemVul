sigar_strerror_get(int err, char *errbuf, int buflen)
{
    char *buf = NULL;
#ifdef WIN32
    DWORD len;

    len = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        err,
                        MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
                        (LPTSTR)errbuf,
                        (DWORD)buflen,
                        NULL);
#else

#if defined(HAVE_STRERROR_R) && defined(HAVE_STRERROR_R_GLIBC)


    buf = strerror_r(err, errbuf, buflen);
#elif defined(HAVE_STRERROR_R)
    if (strerror_r(err, errbuf, buflen) < 0) {
        buf = "Unknown Error";
    }
#else

    buf = strerror(err);
#endif

    if (buf != NULL) {
        SIGAR_STRNCPY(errbuf, buf, buflen);
    }

#endif
    return errbuf;
}
