static int starttls(struct transaction_t *txn, struct http_connection *conn)
{
    int https = (txn == NULL);
    int result;
    SSL_CTX *ctx = NULL;

    if (!conn) conn = txn->conn;

    result=tls_init_serverengine("http",
                                 5,
                                 !https,
                                 &ctx);

    if (result == -1) {
        syslog(LOG_ERR, "error initializing TLS");

        if (txn) txn->error.desc = "Error initializing TLS";
        return HTTP_SERVER_ERROR;
    }

    if (http2_enabled()) {
#ifdef HAVE_TLS_ALPN

        SSL_CTX_set_alpn_select_cb(ctx, alpn_select_cb, conn);
#endif
    }

    if (!https) {

        response_header(HTTP_SWITCH_PROT, txn);
    }

    result=tls_start_servertls(0,
                               1,
                               https ? 180 : httpd_timeout,
                               &saslprops,
                               (SSL **) &conn->tls_ctx);


    if (result == -1) {
        syslog(LOG_NOTICE, "starttls failed: %s", conn->clienthost);

        if (txn) txn->error.desc = "Error negotiating TLS";
        return HTTP_BAD_REQUEST;
    }


    result = saslprops_set_tls(&saslprops, httpd_saslconn);
    if (result != SASL_OK) {
        syslog(LOG_NOTICE, "saslprops_set_tls() failed: cmd_starttls()");
        if (https == 0) {
            fatal("saslprops_set_tls() failed: cmd_starttls()", EX_TEMPFAIL);
        } else {
            shut_down(0);
        }
    }


    prot_settls(httpd_in, conn->tls_ctx);
    prot_settls(httpd_out, conn->tls_ctx);

    httpd_tls_required = 0;

    avail_auth_schemes |= AUTH_BASIC;

    return 0;
}
