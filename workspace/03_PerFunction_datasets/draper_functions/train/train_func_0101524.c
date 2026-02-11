_SSL_check_server_cert(SSL *ssl, const char *hostname)
{
        X509 *cert;
        X509_NAME *subject;
        const GENERAL_NAME *altname;
        STACK_OF(GENERAL_NAME) *altnames;
        ASN1_STRING *tmp;
        int i, n, match = -1;
        const char *p;

        if (SSL_get_verify_mode(ssl) == SSL_VERIFY_NONE ||
            (cert = SSL_get_peer_certificate(ssl)) == NULL) {
                return (1);
        }

        if ((altnames = X509_get_ext_d2i(cert, NID_subject_alt_name,
                    NULL, NULL)) != NULL) {
                n = sk_GENERAL_NAME_num(altnames);

                for (i = 0; i < n && match != 1; i++) {
                        altname = sk_GENERAL_NAME_value(altnames, i);
                        p = (char *)ASN1_STRING_data(altname->d.ia5);
                        if (altname->type == GEN_DNS) {
                                match = (ASN1_STRING_length(altname->d.ia5) ==
                                    strlen(p) && match_pattern(hostname, p));
                        }
                }
                GENERAL_NAMES_free(altnames);
        }

        if (match == -1 &&
            (subject = X509_get_subject_name(cert)) != NULL) {
                for (i = -1; (n = X509_NAME_get_index_by_NID(subject,
                            NID_commonName, i)) >= 0; ) {
                        i = n;
                }
                if (i >= 0) {
                        if ((tmp = X509_NAME_ENTRY_get_data(
                                   X509_NAME_get_entry(subject, i))) != NULL &&
                            ASN1_STRING_type(tmp) == V_ASN1_UTF8STRING) {
                                p = (char *)ASN1_STRING_data(tmp);
                                match = (ASN1_STRING_length(tmp) ==
                                    strlen(p) && match_pattern(hostname, p));
                        }
                }
        }
        X509_free(cert);

        return (match > 0);
}
