static int ocsp_check_issuer(OCSP_BASICRESP *bs, STACK_OF(X509) *chain)
{
    STACK_OF(OCSP_SINGLERESP) *sresp = bs->tbsResponseData.responses;
    X509 *signer, *sca;
    OCSP_CERTID *caid = NULL;
    int ret;

    if (sk_X509_num(chain) <= 0) {
        ERR_raise(ERR_LIB_OCSP, OCSP_R_NO_CERTIFICATES_IN_CHAIN);
        return -1;
    }


    ret = ocsp_check_ids(sresp, &caid);


    if (ret <= 0)
        return ret;

    signer = sk_X509_value(chain, 0);

    if (sk_X509_num(chain) > 1) {
        sca = sk_X509_value(chain, 1);
        ret = ocsp_match_issuerid(sca, caid, sresp);
        if (ret < 0)
            return ret;
        if (ret != 0) {

            if (ocsp_check_delegated(signer))
                return 1;
            return 0;
        }
    }


    return ocsp_match_issuerid(signer, caid, sresp);
}
