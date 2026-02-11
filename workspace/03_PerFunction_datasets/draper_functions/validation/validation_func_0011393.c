PKIX_PL_Cert_GetCERTCertificate(
        PKIX_PL_Cert *cert,
        CERTCertificate **pnssCert,
        void *plContext)
{
    PKIX_ENTER(CERT, "PKIX_PL_Cert_GetNssCert");
    PKIX_NULLCHECK_TWO(cert, pnssCert);

    *pnssCert = CERT_DupCertificate(cert->nssCert);

    PKIX_RETURN(CERT);
}
