static int ocsp_check_ids(STACK_OF(OCSP_SINGLERESP) *sresp, OCSP_CERTID **ret)
{
    OCSP_CERTID *tmpid, *cid;
    int i, idcount;

    idcount = sk_OCSP_SINGLERESP_num(sresp);
    if (idcount <= 0) {
        ERR_raise(ERR_LIB_OCSP, OCSP_R_RESPONSE_CONTAINS_NO_REVOCATION_DATA);
        return -1;
    }

    cid = sk_OCSP_SINGLERESP_value(sresp, 0)->certId;

    *ret = NULL;
    for (i = 1; i < idcount; i++) {
        tmpid = sk_OCSP_SINGLERESP_value(sresp, i)->certId;

        if (OCSP_id_issuer_cmp(cid, tmpid)) {

            if (OBJ_cmp(tmpid->hashAlgorithm.algorithm,
                        cid->hashAlgorithm.algorithm))
                return 2;

            return 0;
        }
    }


    *ret = cid;
    return 1;
}
