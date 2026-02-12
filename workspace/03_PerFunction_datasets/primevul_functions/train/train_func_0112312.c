usm_calc_offsets(size_t globalDataLen,
                 int secLevel, size_t secEngineIDLen, size_t secNameLen, size_t scopedPduLen,
                 u_long engineboots,
                 long engine_time,
                 size_t * theTotalLength,
                 size_t * authParamsOffset,
                 size_t * privParamsOffset,
                 size_t * dataOffset,

                 size_t * datalen,
                 size_t * msgAuthParmLen,
                 size_t * msgPrivParmLen,
                 size_t * otstlen,
                 size_t * seq_len,
                 size_t * msgSecParmLen)
{
    int             engIDlen,
                    engBtlen,
                    engTmlen,
                    namelen,
                    authlen, privlen, ret;


    *msgAuthParmLen = (secLevel == SNMP_SEC_LEVEL_AUTHNOPRIV
                       || secLevel == SNMP_SEC_LEVEL_AUTHPRIV) ? 12 : 0;

    *msgPrivParmLen = (secLevel == SNMP_SEC_LEVEL_AUTHPRIV) ? 8 : 0;


    if ((engIDlen = asn_predict_length(ASN_OCTET_STR,
                                       NULL, secEngineIDLen)) == -1) {
        return -1;
    }

    if ((engBtlen = asn_predict_length(ASN_INTEGER,
                                       (u_char *) & engineboots,
                                       sizeof(long))) == -1) {
        return -1;
    }

    if ((engTmlen = asn_predict_length(ASN_INTEGER,
                                       (u_char *) & engine_time,
                                       sizeof(long))) == -1) {
        return -1;
    }

    if ((namelen = asn_predict_length(ASN_OCTET_STR,
                                      NULL, secNameLen)) == -1) {
        return -1;
    }

    if ((authlen = asn_predict_length(ASN_OCTET_STR,
                                      NULL, *msgAuthParmLen)) == -1) {
        return -1;
    }

    if ((privlen = asn_predict_length(ASN_OCTET_STR,
                                      NULL, *msgPrivParmLen)) == -1) {
        return -1;
    }

    *seq_len =
        engIDlen + engBtlen + engTmlen + namelen + authlen + privlen;

    if ((ret = asn_predict_length(ASN_SEQUENCE,
                                      NULL, *seq_len)) == -1) {
        return -1;
    }
    *otstlen = (size_t)ret;

    if ((ret = asn_predict_length(ASN_OCTET_STR,
                                      NULL, *otstlen)) == -1) {
        return -1;
    }
    *msgSecParmLen = (size_t)ret;

    *authParamsOffset = globalDataLen + +(*msgSecParmLen - *seq_len)
        + engIDlen + engBtlen + engTmlen + namelen
        + (authlen - *msgAuthParmLen);

    *privParamsOffset = *authParamsOffset + *msgAuthParmLen
        + (privlen - *msgPrivParmLen);


    if (secLevel == SNMP_SEC_LEVEL_AUTHPRIV) {
        scopedPduLen = ROUNDUP8(scopedPduLen);

        if ((ret = asn_predict_length(ASN_OCTET_STR, NULL, scopedPduLen)) == -1) {
            return -1;
        }
        *datalen = (size_t)ret;
    } else {
        *datalen = scopedPduLen;
    }

    *dataOffset = globalDataLen + *msgSecParmLen +
        (*datalen - scopedPduLen);
    *theTotalLength = globalDataLen + *msgSecParmLen + *datalen;

    return 0;

}
