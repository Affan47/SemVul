krb5_ldap_delete_krbcontainer(krb5_context context, const char *dn)
{
    LDAP                        *ld=NULL;
    krb5_error_code             st=0;
    kdb5_dal_handle             *dal_handle=NULL;
    krb5_ldap_context           *ldap_context=NULL;
    krb5_ldap_server_handle     *ldap_server_handle=NULL;

    SETUP_CONTEXT ();


    GET_HANDLE ();

    if (dn == NULL) {
        st = EINVAL;
        krb5_set_error_message(context, st,
                               _("Kerberos Container information is missing"));
        goto cleanup;
    }


    if ((st = ldap_delete_ext_s(ld, dn, NULL, NULL)) != LDAP_SUCCESS) {
        int ost = st;
        st = translate_ldap_error (st, OP_ADD);
        krb5_set_error_message(context, st,
                               _("Kerberos Container delete FAILED: %s"),
                               ldap_err2string(ost));
        goto cleanup;
    }

cleanup:

    krb5_ldap_put_handle_to_pool(ldap_context, ldap_server_handle);
    return(st);
}
