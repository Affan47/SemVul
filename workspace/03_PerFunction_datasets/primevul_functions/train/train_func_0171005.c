static char *bignum_to_string(const BIGNUM *bn)
{
    char *tmp, *ret;
    size_t len;


    if (BN_num_bits(bn) < 128)
        return BN_bn2dec(bn);

    tmp = BN_bn2hex(bn);
    if (tmp == NULL)
        return NULL;

    len = strlen(tmp) + 3;
    ret = OPENSSL_malloc(len);
    if (ret == NULL) {
        X509V3err(X509V3_F_BIGNUM_TO_STRING, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(tmp);
        return NULL;
    }


    if (tmp[0] == '-') {
        OPENSSL_strlcpy(ret, "-0x", len);
        OPENSSL_strlcat(ret, tmp + 1, len);
    } else {
        OPENSSL_strlcpy(ret, "0x", len);
        OPENSSL_strlcat(ret, tmp, len);
    }
    OPENSSL_free(tmp);
    return ret;
}
