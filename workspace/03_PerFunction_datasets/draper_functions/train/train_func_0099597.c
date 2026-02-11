krb5_check_password(const char *principal, const char *password)
{
    krb5_error_code code;
    krb5_context ctx;
    krb5_creds creds;
    krb5_principal princ = NULL;
    krb5_get_init_creds_opt opts;
    bool creds_valid = false;
    int result = 0;

    code = krb5_init_context(&ctx);
    if (code != 0) {
        com_err(message_program_name, code, "initializing krb5 context");
        return 0;
    }
    code = krb5_parse_name(ctx, principal, &princ);
    if (code != 0) {
        com_err(message_program_name, code, "parsing principal name %.100s",
                principal);
        goto cleanup;
    }
    memset(&opts, 0, sizeof(opts));
    krb5_get_init_creds_opt_init(&opts);
    krb5_get_init_creds_opt_set_forwardable(&opts, 0);
    krb5_get_init_creds_opt_set_proxiable(&opts, 0);
    code = krb5_get_init_creds_password(ctx, &creds, princ, (char *) password,
                                        NULL, NULL, 0, NULL, &opts);
    if (code == 0) {
        krb5_verify_init_creds_opt vopts;

        creds_valid = true;
        memset(&opts, 0, sizeof(vopts));
        krb5_verify_init_creds_opt_init(&vopts);
        code = krb5_verify_init_creds(ctx, &creds, princ, NULL, NULL, &vopts);
    }
    if (code == 0)
        result = 1;
    else {
        switch (code) {
        case KRB5KRB_AP_ERR_BAD_INTEGRITY:
            com_err(message_program_name, 0, "bad password for %.100s",
                    principal);
            break;
        case KRB5KDC_ERR_C_PRINCIPAL_UNKNOWN:
            com_err(message_program_name, 0, "unknown user %.100s",
                    principal);
            break;
        default:
            com_err(message_program_name, code,
                    "checking Kerberos password for %.100s", principal);
        }
    }

cleanup:
    if (creds_valid)
        krb5_free_cred_contents(ctx, &creds);
    if (princ != NULL)
        krb5_free_principal(ctx, princ);
    krb5_free_context(ctx);
    return result;
}
