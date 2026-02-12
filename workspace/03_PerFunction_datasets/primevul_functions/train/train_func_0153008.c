static int http_auth(const char *creds, struct transaction_t *txn)
{
    struct auth_challenge_t *chal = &txn->auth_chal;
    static int status = SASL_OK;
    int slen, r;
    const char *clientin = NULL, *realm = NULL, *user, **authzid;
    unsigned int clientinlen = 0;
    struct auth_scheme_t *scheme;
    static char base64[BASE64_BUF_SIZE+1];
    const void *canon_user = NULL;


    slen = strcspn(creds, " ");
    if ((clientin = strchr(creds + slen, ' '))) {
        while (strchr(" ", *++clientin));
        clientinlen = strlen(clientin);
    }

    syslog(LOG_DEBUG,
           "http_auth: status=%d   scheme='%s'   creds='%.*s%s'",
           status, chal->scheme ? chal->scheme->name : "",
           slen, creds, clientin ? " <response>" : "");


    if (httpd_userid) {
        free(httpd_userid);
        httpd_userid = NULL;
    }
    if (httpd_extrafolder) {
        free(httpd_extrafolder);
        httpd_extrafolder = NULL;
    }
    if (httpd_extradomain) {
        free(httpd_extradomain);
        httpd_extradomain = NULL;
    }
    if (httpd_authstate) {
        auth_freestate(httpd_authstate);
        httpd_authstate = NULL;
    }
    chal->param = NULL;

    if (chal->scheme) {

        scheme = chal->scheme;

        if (strncasecmp(scheme->name, creds, slen)) {

            syslog(LOG_DEBUG, "http_auth: changing scheme");
            reset_saslconn(&httpd_saslconn);
            chal->scheme = NULL;
            status = SASL_OK;
        }
    }

    if (!chal->scheme) {

        syslog(LOG_DEBUG, "http_auth: find client scheme");
        for (scheme = auth_schemes; scheme->name; scheme++) {
            if (slen && !strncasecmp(scheme->name, creds, slen)) {

                if (!(avail_auth_schemes & scheme->id)) scheme = NULL;
                break;
            }
        }
        if (!scheme || !scheme->name) {

            syslog(LOG_DEBUG, "Unknown auth scheme '%.*s'", slen, creds);
            return SASL_NOMECH;
        }

        syslog(LOG_DEBUG, "http_auth: found matching scheme: %s", scheme->name);
        chal->scheme = scheme;
        status = SASL_OK;

        if (!clientin && (scheme->flags & AUTH_REALM_PARAM)) {

            switch (txn->req_tgt.namespace->id) {
            case URL_NS_DEFAULT:
            case URL_NS_PRINCIPAL:
                realm = config_getstring(IMAPOPT_DAV_REALM);
                break;

            case URL_NS_CALENDAR:
                realm = config_getstring(IMAPOPT_CALDAV_REALM);
                break;

            case URL_NS_ADDRESSBOOK:
                realm = config_getstring(IMAPOPT_CARDDAV_REALM);
                break;

            case URL_NS_RSS:
                realm = config_getstring(IMAPOPT_RSS_REALM);
                break;
            }
            if (!realm) realm = config_servername;


            snprintf(base64, BASE64_BUF_SIZE, "realm=\"%s\"", realm);
            chal->param = base64;
            chal->scheme = NULL;
            return status;
        }
    }


    if (clientin && (scheme->flags & AUTH_DATA_PARAM)) {
        const char *sid = NULL;
        unsigned int sid_len;

        r = http_parse_auth_params(clientin, NULL , NULL,
                                   &sid, &sid_len, &clientin, &clientinlen);
        if (r != SASL_OK) return r;

        if (sid) {
            const char *mysid = session_id();

            if (sid_len != strlen(mysid) ||
                strncmp(mysid, sid, sid_len)) {
                syslog(LOG_ERR, "%s: Incorrect 'sid' parameter in credentials",
                       scheme->name);
                return SASL_BADAUTH;
            }
        }
    }


    if (clientin && (scheme->flags & AUTH_BASE64)) {
        r = sasl_decode64(clientin, clientinlen,
                          base64, BASE64_BUF_SIZE, &clientinlen);
        if (r != SASL_OK) {
            syslog(LOG_ERR, "Base64 decode failed: %s",
                   sasl_errstring(r, NULL, NULL));
            return r;
        }
        clientin = base64;
    }

    if (scheme->id == AUTH_BASIC) {

        char *pass;
        char *extra;
        char *plus;
        char *domain;


        user = base64;
        pass = strchr(base64, ':');
        if (!pass) {
            syslog(LOG_ERR, "Basic auth: Missing password");
            return SASL_BADPARAM;
        }
        *pass++ = '\0';
        domain = strchr(user, '@');
        if (domain) *domain++ = '\0';
        extra = strchr(user, '%');
        if (extra) *extra++ = '\0';
        plus = strchr(user, '+');
        if (plus) *plus++ = '\0';


        char *realuser =
            domain ? strconcat(user, "@", domain, (char *) NULL) : xstrdup(user);

        status = sasl_checkpass(httpd_saslconn, realuser, strlen(realuser),
                                pass, strlen(pass));
        memset(pass, 0, strlen(pass));

        if (status) {
            syslog(LOG_NOTICE, "badlogin: %s Basic %s %s",
                   txn->conn->clienthost, realuser,
                   sasl_errdetail(httpd_saslconn));
            free(realuser);


            if (status == SASL_NOUSER) status = SASL_BADAUTH;
            return status;
        }
        free(realuser);


        httpd_extrafolder = xstrdupnull(plus);
        httpd_extradomain = xstrdupnull(extra);
    }
    else if (scheme->id == AUTH_BEARER) {

        assert(txn->req_tgt.namespace->bearer);


        base64[0] = 0;
        status = txn->req_tgt.namespace->bearer(clientin,
                                                base64, BASE64_BUF_SIZE);
        if (status) return status;
        canon_user = user = base64;


        httpd_extrafolder = NULL;
        httpd_extradomain = NULL;
        httpd_authstate = auth_newstate(user);
    }
    else {

        const char *serverout = NULL;
        unsigned int serveroutlen = 0;
        unsigned int auth_params_len = 0;

#ifdef SASL_HTTP_REQUEST

        sasl_http_request_t sasl_http_req;

        if (scheme->flags & AUTH_NEED_REQUEST) {
            sasl_http_req.method = txn->req_line.meth;
            sasl_http_req.uri = txn->req_line.uri;
            sasl_http_req.entity = NULL;
            sasl_http_req.elen = 0;
            sasl_http_req.non_persist = txn->flags.conn & CONN_CLOSE;
            sasl_setprop(httpd_saslconn, SASL_HTTP_REQUEST, &sasl_http_req);
        }
#endif

        if (status == SASL_CONTINUE) {

            syslog(LOG_DEBUG, "http_auth: continue %s", scheme->saslmech);
            status = sasl_server_step(httpd_saslconn, clientin, clientinlen,
                                      &serverout, &serveroutlen);
        }
        else {

            syslog(LOG_DEBUG, "http_auth: start %s", scheme->saslmech);
            status = sasl_server_start(httpd_saslconn, scheme->saslmech,
                                       clientin, clientinlen,
                                       &serverout, &serveroutlen);
        }


        if ((status != SASL_OK) && (status != SASL_CONTINUE)) {
            syslog(LOG_ERR, "SASL failed: %s",
                   sasl_errstring(status, NULL, NULL));
            return status;
        }


        if (scheme->flags & AUTH_DATA_PARAM) {
            auth_params_len = snprintf(base64,
                                       MAX_AUTHPARAM_SIZE + MAX_SESSIONID_SIZE,
                                       "sid=%s%s", session_id(),
                                       serverout ? ",data=" : "");
        }


        if (serverout && (scheme->flags & AUTH_BASE64)) {
            r = sasl_encode64(serverout, serveroutlen,
                              base64 + auth_params_len, MAX_BASE64_SIZE, NULL);
            if (r != SASL_OK) {
                syslog(LOG_ERR, "Base64 encode failed: %s",
                       sasl_errstring(r, NULL, NULL));
                return r;
            }
            serverout = base64;
        }

        chal->param = serverout;

        if (status == SASL_CONTINUE) {

            return status;
        }


    }

    if (!canon_user) {

        status = sasl_getprop(httpd_saslconn, SASL_USERNAME, &canon_user);
        if (status != SASL_OK) {
            syslog(LOG_ERR, "weird SASL error %d getting SASL_USERNAME", status);
            return status;
        }
        user = (const char *) canon_user;
    }

    if (httpd_authid) free(httpd_authid);
    httpd_authid = xstrdup(user);

    authzid = spool_getheader(txn->req_hdrs, "Authorize-As");
    if (authzid && *authzid[0]) {

        user = authzid[0];

        status = proxy_authz(&user, txn);
        if (status) return status;
    }


    r = auth_success(txn, user);
    if (r == HTTP_UNAVAILABLE) {
        status = SASL_UNAVAIL;
    }
    else if (r) {


        syslog(LOG_ERR, "auth_success returned error: %s", error_message(r));
        status = SASL_FAIL;
    }

    return status;
}
