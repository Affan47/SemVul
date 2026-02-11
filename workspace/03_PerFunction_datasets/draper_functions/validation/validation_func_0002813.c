_asn_build_header_check(const char *str, const u_char * data,
                        size_t datalen, size_t typedlen)
{
    char            ebuf[128];

    if (data == NULL) {


        return 1;
    }
    if (datalen < typedlen) {
        snprintf(ebuf, sizeof(ebuf),
                "%s: bad header, length too short: %lu < %lu", str,
                (unsigned long)datalen, (unsigned long)typedlen);
        ebuf[ sizeof(ebuf)-1 ] = 0;
        ERROR_MSG(ebuf);
        return 1;
    }
    return 0;
}
