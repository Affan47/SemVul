proctable_unlock(request_rec *r)
{

    apr_status_t rv;

    if ((rv = proctable_unlock_internal()) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_EMERG, rv, r,
                      "mod_fcgid: can't unlock process table in pid %"
                      APR_PID_T_FMT,
                      getpid());
        exit(1);
    }
}
