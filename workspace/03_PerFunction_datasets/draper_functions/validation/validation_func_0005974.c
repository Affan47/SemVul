strerror(const int errnum,
                                 char *buf,
                                 const size_t buflen)
{
    const char *result = "";
    if ((buf != NULL) && (buflen > 0))
    {

        buf[0] = 0;

#ifdef HAVE_CHARP_STRERROR_R


        result = strerror_r(errnum, buf, buflen);
#else

        (void) strerror_r(errnum, buf, buflen);
        result = buf;
#endif
    }
    return result;
}
