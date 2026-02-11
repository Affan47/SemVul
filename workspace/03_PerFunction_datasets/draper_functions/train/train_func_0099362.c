get_default_privtype(size_t * len)
{
    if (defaultPrivType == NULL) {
#ifndef NETSNMP_DISABLE_DES
        defaultPrivType = usmDESPrivProtocol;
#else
        defaultPrivType = usmAESPrivProtocol;
#endif
        defaultPrivTypeLen = USM_LENGTH_OID_TRANSFORM;
    }
    if (len)
        *len = defaultPrivTypeLen;
    return defaultPrivType;
}
