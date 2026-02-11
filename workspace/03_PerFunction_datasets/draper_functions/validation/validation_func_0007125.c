xmlSecGnuTLSX509FindSignerCert(xmlSecPtrListPtr certs, gnutls_x509_crt_t cert) {
    gnutls_x509_crt_t res = NULL;
    xmlChar * issuer = NULL;
    xmlSecSize ii, sz;

    xmlSecAssert2(certs != NULL, NULL);
    xmlSecAssert2(cert != NULL, NULL);


    issuer = xmlSecGnuTLSX509CertGetIssuerDN(cert);
    if(issuer == NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecGnuTLSX509CertGetIssuerDN",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        goto done;
    }


    sz = xmlSecPtrListGetSize(certs);
    for(ii = 0; (ii < sz) && (res == NULL); ++ii) {
        gnutls_x509_crt_t tmp;
        xmlChar * subject;

        tmp = xmlSecPtrListGetItem(certs, ii);
        if(tmp == NULL) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        NULL,
                        "xmlSecPtrListGetItem",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        "pos=%i", (int)ii);
            goto done;
        }

        subject = xmlSecGnuTLSX509CertGetSubjectDN(tmp);
        if(subject == NULL) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        NULL,
                        "xmlSecGnuTLSX509CertGetSubjectDN",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        "pos=%i", (int)ii);
            goto done;
        }


        if((xmlSecGnuTLSX509DnsEqual(issuer, subject) == 1)) {
            res = tmp;
        }
        xmlFree(subject);
    }

done:
    if(issuer != NULL) {
        xmlFree(issuer);
    }
    return(res);
}
