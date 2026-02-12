int Socket::checkCertHostname(const std::string &_hostname)
{
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    String hostname = _hostname;

    X509 *peercertificate = SSL_get_peer_certificate(ssl);
    if (peercertificate == NULL) {
#ifdef NETDEBUG
        std::cout << thread_id << "unable to get certificate for " << hostname << std::endl;
#endif
        return -1;
    }

    hostname.toLower();

#ifdef NETDEBUG
    std::cout << thread_id << "checking certificate" << hostname << std::endl;
    std::cout << thread_id << "Checking hostname against subjectAltNames" << std::endl;
#endif


    bool matched = false;
    bool hasaltname = false;


    STACK_OF(GENERAL_NAME) *gens = NULL;
    gens = (STACK_OF(GENERAL_NAME) *)X509_get_ext_d2i(peercertificate, NID_subject_alt_name, 0, 0);
    int r = sk_GENERAL_NAME_num(gens);
    for (int i = 0; i < r; ++i) {
        const GENERAL_NAME *gn = sk_GENERAL_NAME_value(gens, i);


        if (gn->type != GEN_DNS) {
            continue;
        }


        hasaltname = true;


        unsigned char *nameutf8;
        int len = ASN1_STRING_to_UTF8(&nameutf8, gn->d.ia5);
        if (len < 0) {
            break;
        }

        String altname = std::string((char *)nameutf8, len);
        OPENSSL_free(nameutf8);


        altname.toLower();

#ifdef NETDEBUG
        std::cout << thread_id << "checking against alt name " << altname << std::endl;
#endif

        if (hostname.compare(altname) == 0) {
            matched = true;
            break;
        } else if (altname.contains("*")) {
#ifdef NETDEBUG
            std::cout << thread_id << "Wildcard certificate is in use" << std::endl;
#endif
            String  anend;
            anend = altname.after("*");
            if (hostname.endsWith(anend)) {
                bool part_match = true;
                String anstart = altname.before("*");
                String t = hostname.before(anend.c_str());
                if( anstart.length() > 0) {
                  if( hostname.startsWith(anstart)) {
                    t = t.after(anstart.c_str());
                  } else {
                      part_match = false;
                   }
                 }

                 if (part_match && !t.contains(".")) {
                   matched = true;
                   break;
                }
            }
        }
    }
    sk_GENERAL_NAME_pop_free(gens, GENERAL_NAME_free);

    if (matched) {
        X509_free(peercertificate);
        return 0;
    } else if (hasaltname) {
        X509_free(peercertificate);
        return -1;
    }

#ifdef NETDEBUG
    std::cout << thread_id << "checking hostname against the following common names" << std::endl;
#endif

    X509_NAME *name = X509_get_subject_name(peercertificate);

    int current_entry = -1;
    while (1) {


        current_entry = X509_NAME_get_index_by_NID(name, NID_commonName, current_entry);
        if (current_entry == -1) {

            break;
        }


        X509_NAME_ENTRY *entry = X509_NAME_get_entry(name, current_entry);

        ASN1_STRING *asn1name = X509_NAME_ENTRY_get_data(entry);

        unsigned char *nameutf8;
        int len = ASN1_STRING_to_UTF8(&nameutf8, asn1name);
        if (len < 0) {
            break;
        }
        String commonname = std::string((char *)nameutf8, len);

        OPENSSL_free(nameutf8);


        commonname.toLower();

#ifdef NETDEBUG
        std::cout << thread_id << "checking against common name " << commonname << std::endl;
#endif


        if (hostname.compare(commonname) == 0) {
            matched = true;
            break;
        }

        else if (commonname.startsWith("*.")) {
#ifdef NETDEBUG
            std::cout << thread_id << "Wildcard certificate is in use" << std::endl;
#endif
            commonname = commonname.after("*");

            if (hostname.endsWith(commonname)) {
                matched = true;
                break;
            }
        }
    }

    if (matched) {
        X509_free(peercertificate);
        return 0;
    }
#else
    return 0;
#endif
    return -1;
}
