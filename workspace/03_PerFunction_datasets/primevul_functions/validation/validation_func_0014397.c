static apr_status_t ap_session_save(request_rec * r, session_rec * z)
{
    if (z) {
        apr_time_t now = apr_time_now();
        apr_time_t initialExpiry = z->expiry;
        int rv = 0;

        session_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                       &session_module);


        if (z->written) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01818)
                          "attempt made to save the session twice, "
                          "session not saved: %s", r->uri);
            return APR_EGENERAL;
        }
        if (z->expiry && z->expiry < now) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01819)
                          "attempt made to save a session when the session had already expired, "
                          "session not saved: %s", r->uri);
            return APR_EGENERAL;
        }


        if (dconf->maxage) {
            z->expiry = now + dconf->maxage * APR_USEC_PER_SEC;
            z->maxage = dconf->maxage;
        }


        if (z->dirty && z->maxage) {
            z->expiry = now + z->maxage * APR_USEC_PER_SEC;
        }


        if (!z->dirty && dconf->expiry_update_time
                && (z->expiry - initialExpiry < dconf->expiry_update_time)) {
            return APR_SUCCESS;
        }


        if (!z->dirty && !z->maxage) {
            return APR_SUCCESS;
        }


        rv = ap_run_session_encode(r, z);
        if (OK != rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01820)
                          "error while encoding the session, "
                          "session not saved: %s", r->uri);
            return rv;
        }


        rv = ap_run_session_save(r, z);
        if (DECLINED == rv) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01821)
                          "session is enabled but no session modules have been configured, "
                          "session not saved: %s", r->uri);
            return APR_EGENERAL;
        }
        else if (OK != rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01822)
                          "error while saving the session, "
                          "session not saved: %s", r->uri);
            return rv;
        }
        else {
            z->written = 1;
        }
    }

    return APR_SUCCESS;

}
