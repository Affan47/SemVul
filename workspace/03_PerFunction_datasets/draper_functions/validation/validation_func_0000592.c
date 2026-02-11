SEC_PKCS7CreateSignedData (CERTCertificate *cert,
			   SECCertUsage certusage,
			   CERTCertDBHandle *certdb,
			   SECOidTag digestalg,
			   SECItem *digest,
 			   SECKEYGetPasswordKey pwfn, void *pwfn_arg)
{
    SEC_PKCS7ContentInfo *cinfo;
    SECStatus rv;

    cinfo = sec_pkcs7_create_signed_data (pwfn, pwfn_arg);
    if (cinfo == NULL)
	return NULL;

    rv = sec_pkcs7_add_signer (cinfo, cert, certusage, certdb,
			       digestalg, digest);
    if (rv != SECSuccess) {
	SEC_PKCS7DestroyContentInfo (cinfo);
	return NULL;
    }

    return cinfo;
}
