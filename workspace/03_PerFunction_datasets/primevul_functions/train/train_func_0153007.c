static int auth_check_hdrs(struct transaction_t *txn, int *sasl_result)
{
    int ret = 0, r = 0;
    const char **hdr;

    if (txn->flags.redirect) return 0;


    if ((hdr = spool_getheader(txn->req_hdrs, "Authorization"))) {
        if (httpd_userid) {

            syslog(LOG_DEBUG, "reauth - reinit");
            reset_saslconn(&httpd_saslconn);
            txn->auth_chal.scheme = NULL;
        }

        if (httpd_tls_required) {

            ret = HTTP_UNAUTHORIZED;
        }
        else {

            r = http_auth(hdr[0], txn);
            if ((r < 0) || !txn->auth_chal.scheme) {

                syslog(LOG_DEBUG, "auth failed - reinit");
                reset_saslconn(&httpd_saslconn);
                txn->auth_chal.scheme = NULL;
                if (r == SASL_UNAVAIL) {


                    ret = HTTP_UNAVAILABLE;
                }
                else if (r == SASL_FAIL) {
                    ret = HTTP_SERVER_ERROR;
                }
                else {
                    ret = HTTP_UNAUTHORIZED;
                }
            }
            else if (r == SASL_CONTINUE) {

                ret = HTTP_UNAUTHORIZED;
            }
        }
    }
    else if (!httpd_userid && txn->auth_chal.scheme) {

        syslog(LOG_DEBUG, "client didn't complete auth - reinit");
        reset_saslconn(&httpd_saslconn);
        txn->auth_chal.scheme = NULL;
    }


    else if (!config_mupdate_server || !config_getstring(IMAPOPT_PROXYSERVERS)) {
        syslog(LOG_DEBUG, "drop auth creds");

        free(httpd_userid);
        httpd_userid = NULL;

        free(httpd_extrafolder);
        httpd_extrafolder = NULL;

        free(httpd_extradomain);
        httpd_extradomain = NULL;

        if (httpd_authstate) {
            auth_freestate(httpd_authstate);
            httpd_authstate = NULL;
        }
    }


    else if (httpd_authid &&
             (hdr = spool_getheader(txn->req_hdrs, "Authorize-As")) &&
             *hdr[0]) {
        const char *authzid = hdr[0];

        r = proxy_authz(&authzid, txn);
        if (r) {

            syslog(LOG_DEBUG, "proxy authz failed - reinit");
            reset_saslconn(&httpd_saslconn);
            txn->auth_chal.scheme = NULL;
            ret = HTTP_UNAUTHORIZED;
        }
        else {
            ret = auth_success(txn, authzid);
        }
    }

    *sasl_result = r;

    return ret;
}
