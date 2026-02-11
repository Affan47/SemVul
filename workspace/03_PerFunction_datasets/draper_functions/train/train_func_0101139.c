cert_ProcessingParamsSetKeyAndCertUsage(
    PKIX_ProcessingParams *procParams,
    SECCertUsage           requiredCertUsage,
    PRUint32               requiredKeyUsages,
    void                  *plContext)
{
    PKIX_CertSelector     *certSelector = NULL;
    PKIX_ComCertSelParams *certSelParams = NULL;
    PKIX_PL_NssContext    *nssContext = (PKIX_PL_NssContext*)plContext;

    PKIX_ENTER(CERTVFYPKIX, "cert_ProcessingParamsSetKeyAndCertUsage");
    PKIX_NULLCHECK_TWO(procParams, nssContext);

    PKIX_CHECK(
        pkix_pl_NssContext_SetCertUsage(
	    ((SECCertificateUsage)1) << requiredCertUsage, nssContext),
	    PKIX_NSSCONTEXTSETCERTUSAGEFAILED);

    if (requiredKeyUsages) {
        PKIX_CHECK(
            PKIX_ProcessingParams_GetTargetCertConstraints(procParams,
                                                           &certSelector, plContext),
            PKIX_PROCESSINGPARAMSGETTARGETCERTCONSTRAINTSFAILED);

        PKIX_CHECK(
            PKIX_CertSelector_GetCommonCertSelectorParams(certSelector,
                                                          &certSelParams, plContext),
            PKIX_CERTSELECTORGETCOMMONCERTSELECTORPARAMSFAILED);


        PKIX_CHECK(
            PKIX_ComCertSelParams_SetKeyUsage(certSelParams, requiredKeyUsages,
                                              plContext),
            PKIX_COMCERTSELPARAMSSETKEYUSAGEFAILED);
    }
cleanup:
    PKIX_DECREF(certSelector);
    PKIX_DECREF(certSelParams);

    PKIX_RETURN(CERTVFYPKIX);
}
