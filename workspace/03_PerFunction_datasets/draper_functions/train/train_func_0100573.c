check_reply_server(krb5_context context, krb5_flags kdcoptions,
                   krb5_creds *in_cred, krb5_kdc_rep *dec_rep)
{

    if (!krb5_principal_compare(context, dec_rep->ticket->server,
                                dec_rep->enc_part2->server))
        return KRB5_KDCREP_MODIFIED;


    if (krb5_principal_compare(context, dec_rep->ticket->server,
                               in_cred->server))
        return 0;


    if (kdcoptions & KDC_OPT_CANONICALIZE) {


        TRACE_CHECK_REPLY_SERVER_DIFFERS(context, in_cred->server,
                                         dec_rep->enc_part2->server);
        return 0;
    }


    if (!IS_TGS_PRINC(in_cred->server) ||
        !IS_TGS_PRINC(dec_rep->ticket->server)) {

        return KRB5_KDCREP_MODIFIED;
    }
#if 0


    if (krb5_realm_compare(context, in_cred->client, in_cred->server) &&
        data_eq(*in_cred->server->data[1], *in_cred->client->realm)) {

        return KRB5_KDCREP_MODIFIED;
    }
#endif
    return 0;
}
