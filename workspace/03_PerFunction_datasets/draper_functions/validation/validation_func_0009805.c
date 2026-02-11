handle_id_token(const struct webauth_token_id *id, MWA_REQ_CTXT *rc)
{
    const char *mwa_func = "handle_id_token";
    const char *subject, *authz_subject;
    unsigned long now;

    now = time(NULL);
    if (id->creation + rc->sconf->token_max_ttl < now) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, rc->r->server,
                     "mod_webauth: %s: id token too old", mwa_func);
        return 0;
    }


    authz_subject = id->authz_subject;
    if (id->auth_data != NULL) {
        MWA_CRED_INTERFACE *mci;

        mci = mwa_find_cred_interface(rc->r->server, id->auth);
        if (mci == NULL)
            return 0;
        subject = mci->validate_sad(rc, id->auth_data, id->auth_data_len);
        authz_subject = NULL;
    } else if (strcmp(id->auth, "webkdc") == 0) {
        subject = id->subject;
    } else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, rc->r->server,
                     "mod_webauth: %s: unknown subject auth type: %s",
                     mwa_func, id->auth);
        subject = NULL;
    }


    if (subject != NULL) {
        if (rc->sconf->debug)
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, rc->r->server,
                         "mod_webauth: %s: got subject(%s) from id token",
                         mwa_func, subject);
        make_app_cookie(subject, authz_subject, 0, id->expiration, 0,
                        id->initial_factors, id->session_factors, id->loa, rc);
    } else {

    }
    return subject != NULL;
}
