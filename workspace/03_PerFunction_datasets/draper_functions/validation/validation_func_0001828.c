process_option_identity(krb5_context context,
                        pkinit_plg_crypto_context plg_cryptoctx,
                        pkinit_req_crypto_context req_cryptoctx,
                        pkinit_identity_opts *idopts,
                        pkinit_identity_crypto_context id_cryptoctx,
                        const char *value)
{
    const char *residual;
    int idtype;
    krb5_error_code retval = 0;

    pkiDebug("%s: processing value '%s'\n",
             __FUNCTION__, value ? value : "NULL");
    if (value == NULL)
        return EINVAL;

    residual = strchr(value, ':');
    if (residual != NULL) {
        unsigned int typelen;
        residual++;
        typelen = residual - value;
        if (strncmp(value, "FILE:", typelen) == 0) {
            idtype = IDTYPE_FILE;
#ifndef WITHOUT_PKCS11
        } else if (strncmp(value, "PKCS11:", typelen) == 0) {
            idtype = IDTYPE_PKCS11;
#endif
        } else if (strncmp(value, "PKCS12:", typelen) == 0) {
            idtype = IDTYPE_PKCS12;
        } else if (strncmp(value, "DIR:", typelen) == 0) {
            idtype = IDTYPE_DIR;
        } else if (strncmp(value, "ENV:", typelen) == 0) {
            idtype = IDTYPE_ENVVAR;
#ifdef PKINIT_CRYPTO_IMPL_NSS
        } else if (strncmp(value, "NSS:", typelen) == 0) {
            idtype = IDTYPE_NSS;
#endif
        } else {
            pkiDebug("%s: Unsupported type while processing '%s'\n",
                     __FUNCTION__, value);
            krb5_set_error_message(context, KRB5_PREAUTH_FAILED,
                                   _("Unsupported type while processing "
                                     "'%s'\n"), value);
            return KRB5_PREAUTH_FAILED;
        }
    } else {
        idtype = IDTYPE_FILE;
        residual = value;
    }

    idopts->idtype = idtype;
    pkiDebug("%s: idtype is %s\n", __FUNCTION__, idtype2string(idopts->idtype));
    switch (idtype) {
    case IDTYPE_ENVVAR:
        return process_option_identity(context, plg_cryptoctx, req_cryptoctx,
                                       idopts, id_cryptoctx, getenv(residual));
        break;
    case IDTYPE_FILE:
        retval = parse_fs_options(context, idopts, residual);
        break;
    case IDTYPE_PKCS12:
        retval = parse_pkcs12_options(context, idopts, residual);
        break;
#ifndef WITHOUT_PKCS11
    case IDTYPE_PKCS11:
        retval = parse_pkcs11_options(context, idopts, residual);
        break;
#endif
    case IDTYPE_DIR:
        idopts->cert_filename = strdup(residual);
        if (idopts->cert_filename == NULL)
            retval = ENOMEM;
        break;
#ifdef PKINIT_CRYPTO_IMPL_NSS
    case IDTYPE_NSS:
        idopts->cert_filename = strdup(residual);
        if (idopts->cert_filename == NULL)
            retval = ENOMEM;
        break;
#endif
    default:
        krb5_set_error_message(context, KRB5_PREAUTH_FAILED,
                               _("Internal error parsing "
                                 "X509_user_identity\n"));
        retval = EINVAL;
        break;
    }
    return retval;
}
