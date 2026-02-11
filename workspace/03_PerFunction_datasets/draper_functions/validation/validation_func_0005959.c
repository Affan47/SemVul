NSS_CMSEncryptedData_Encode_BeforeData(NSSCMSEncryptedData *encd)
{
    NSSCMSContentInfo *cinfo;
    PK11SymKey *bulkkey;
    SECAlgorithmID *algid;
    SECStatus rv;

    cinfo = &(encd->contentInfo);


    bulkkey = NSS_CMSContentInfo_GetBulkKey(cinfo);
    if (bulkkey == NULL)
	return SECFailure;
    algid = NSS_CMSContentInfo_GetContentEncAlg(cinfo);
    if (algid == NULL)
	return SECFailure;

    rv = NSS_CMSContentInfo_Private_Init(cinfo);
    if (rv != SECSuccess) {
	return SECFailure;
    }


    cinfo->privateInfo->ciphcx = NSS_CMSCipherContext_StartEncrypt(encd->cmsg->poolp, bulkkey, algid);
    PK11_FreeSymKey(bulkkey);
    if (cinfo->privateInfo->ciphcx == NULL)
	return SECFailure;

    return SECSuccess;
}
