EXPORTED void response_header(long code, struct transaction_t *txn)
{
    int i;
    time_t now;
    char datestr[30];
    double cmdtime, nettime;
    const char **hdr, *sep;
    struct auth_challenge_t *auth_chal = &txn->auth_chal;
    struct resp_body_t *resp_body = &txn->resp_body;
    struct buf *logbuf = &txn->conn->logbuf;
    const char *upgrd_tokens[] =
        { TLS_VERSION, NGHTTP2_CLEARTEXT_PROTO_VERSION_ID, WS_TOKEN, NULL };
    const char *te[] = { "deflate", "gzip", "chunked", NULL };
    const char *ce[] = { "deflate", "gzip", "br", "zstd", NULL };


    alarm(0);
    gotsigalrm = 0;


    begin_resp_headers(txn, code);


    switch (code) {
    default:

        now = time(0);
        httpdate_gen(datestr, sizeof(datestr), now);
        simple_hdr(txn, "Date", datestr);


        GCC_FALLTHROUGH

    case HTTP_SWITCH_PROT:
        if (txn->flags.conn && (txn->flags.ver < VER_2)) {

            const char *conn_tokens[] =
                { "close", "Upgrade", "Keep-Alive", NULL };

            comma_list_hdr(txn, "Connection", conn_tokens, txn->flags.conn);

            if (txn->flags.upgrade) {

                comma_list_hdr(txn, "Upgrade", upgrd_tokens, txn->flags.upgrade);

                if (txn->flags.upgrade & UPGRADE_WS) {

                    ws_add_resp_hdrs(txn);
                }
            }
            if (txn->flags.conn & CONN_KEEPALIVE) {
                simple_hdr(txn, "Keep-Alive", "timeout=%d", httpd_timeout);
            }
        }


        GCC_FALLTHROUGH

    case HTTP_EARLY_HINTS:
        for (i = 0; i < strarray_size(&resp_body->links); i++) {
            simple_hdr(txn, "Link", strarray_nth(&resp_body->links, i));
        }

        if (code >= HTTP_OK) break;


        GCC_FALLTHROUGH

    case HTTP_CONTINUE:
    case HTTP_PROCESSING:

        end_resp_headers(txn, code);


        prot_flush(httpd_out);


        if (!txn->ws_ctx && (txn->flags.ver == VER_1_1)) alarm(httpd_keepalive);

        goto log;
    }


    if (txn->conn->tls_ctx) {
        simple_hdr(txn, "Strict-Transport-Security", "max-age=600");
    }
    if (txn->location) {
        simple_hdr(txn, "Location", txn->location);
    }
    if (txn->flags.mime) {
        simple_hdr(txn, "MIME-Version", "1.0");
    }
    if (txn->flags.cc) {

        const char *cc_dirs[] =
            { "must-revalidate", "no-cache", "no-store", "no-transform",
              "public", "private", "max-age=%d", NULL };

        comma_list_hdr(txn, "Cache-Control",
                       cc_dirs, txn->flags.cc, resp_body->maxage);

        if (txn->flags.cc & CC_MAXAGE) {
            httpdate_gen(datestr, sizeof(datestr), now + resp_body->maxage);
            simple_hdr(txn, "Expires", datestr);
        }
    }
    if (txn->flags.cors) {

        simple_hdr(txn, "Access-Control-Allow-Origin",
                      *spool_getheader(txn->req_hdrs, "Origin"));
        simple_hdr(txn, "Access-Control-Allow-Credentials", "true");

        if (txn->flags.cors == CORS_PREFLIGHT) {
            allow_hdr(txn, "Access-Control-Allow-Methods", txn->req_tgt.allow);

            for (hdr = spool_getheader(txn->req_hdrs,
                                       "Access-Control-Request-Headers");
                 hdr && *hdr; hdr++) {
                simple_hdr(txn, "Access-Control-Allow-Headers", *hdr);
            }
            simple_hdr(txn, "Access-Control-Max-Age", "3600");
        }
    }
    if (txn->flags.vary && !(txn->flags.cc & CC_NOCACHE)) {

        const char *vary_hdrs[] = { "Accept", "Accept-Encoding", "Brief",
                                    "Prefer", "If-None-Match",
                                    "CalDAV-Timezones", NULL };

        comma_list_hdr(txn, "Vary", vary_hdrs, txn->flags.vary);
    }


    if (code == HTTP_UNAUTHORIZED) {
        if (!auth_chal->scheme) {

            list_auth_schemes(txn);
        }
        else {

            WWW_Authenticate(auth_chal->scheme->name, auth_chal->param);
        }
    }
    else if (auth_chal->param) {

        if (auth_chal->scheme->flags & AUTH_SUCCESS_WWW) {

            WWW_Authenticate(auth_chal->scheme->name, auth_chal->param);
        }
        else {

            simple_hdr(txn, "Authentication-Info", auth_chal->param);
        }
    }


    if (txn->req_tgt.allow & ALLOW_ISCHEDULE) {
        simple_hdr(txn, "iSchedule-Version", "1.0");

        if (resp_body->iserial) {
            simple_hdr(txn, "iSchedule-Capabilities", "%ld", resp_body->iserial);
        }
    }
    if (resp_body->patch) {
        accept_patch_hdr(txn, resp_body->patch);
    }

    switch (code) {
    case HTTP_OK:
        switch (txn->meth) {
        case METH_CONNECT:
            if (txn->ws_ctx) {

                ws_add_resp_hdrs(txn);
            }
            break;

        case METH_GET:
        case METH_HEAD:

            simple_hdr(txn, "Accept-Ranges",
                       txn->flags.ranges ? "bytes" : "none");
            break;

        case METH_OPTIONS:
            if (config_serverinfo == IMAP_ENUM_SERVERINFO_ON) {
                simple_hdr(txn, "Server", buf_cstring(&serverinfo));
            }

            if (!httpd_userid && !auth_chal->scheme) {

                list_auth_schemes(txn);
            }

            if (txn->req_tgt.allow & ALLOW_DAV) {

                simple_hdr(txn, "DAV", "1, 2, 3, access-control,"
                           " extended-mkcol, resource-sharing");
                if (txn->req_tgt.allow & ALLOW_CAL) {
                    simple_hdr(txn, "DAV", "calendar-access%s%s",
                               (txn->req_tgt.allow & ALLOW_CAL_SCHED) ?
                               ", calendar-auto-schedule" : "",
                               (txn->req_tgt.allow & ALLOW_CAL_NOTZ) ?
                               ", calendar-no-timezone" : "");
                    simple_hdr(txn, "DAV", "calendar-query-extended%s%s",
                               (txn->req_tgt.allow & ALLOW_CAL_AVAIL) ?
                               ", calendar-availability" : "",
                               (txn->req_tgt.allow & ALLOW_CAL_ATTACH) ?
                               ", calendar-managed-attachments" : "");


                    simple_hdr(txn, "DAV", "calendarserver-sharing%s",
                               (txn->req_tgt.allow &
                                (ALLOW_CAL_AVAIL | ALLOW_CAL_SCHED)) ==
                               (ALLOW_CAL_AVAIL | ALLOW_CAL_SCHED) ?
                               ", inbox-availability" : "");
                }
                if (txn->req_tgt.allow & ALLOW_CARD) {
                    simple_hdr(txn, "DAV", "addressbook");
                }
            }


            if (txn->flags.cors != CORS_PREFLIGHT) {

                allow_hdr(txn, "Allow", txn->req_tgt.allow);
            }
            break;
        }
        break;

    case HTTP_NOT_ALLOWED:

        allow_hdr(txn, "Allow", txn->req_tgt.allow);
        break;

    case HTTP_BAD_CE:

        if (accept_encodings) {
            comma_list_hdr(txn, "Accept-Encoding", ce, accept_encodings);
        }
        else simple_hdr(txn, "Accept-Encoding", "identity");
        break;
    }


    if (resp_body->lock) {
        simple_hdr(txn, "Lock-Token", "<%s>", resp_body->lock);
        if (txn->flags.cors) Access_Control_Expose("Lock-Token");
    }
    if (resp_body->ctag) {
        simple_hdr(txn, "CTag", "%s", resp_body->ctag);
        if (txn->flags.cors) Access_Control_Expose("CTag");
    }
    if (resp_body->stag) {
        simple_hdr(txn, "Schedule-Tag", "\"%s\"", resp_body->stag);
        if (txn->flags.cors) Access_Control_Expose("Schedule-Tag");
    }
    if (resp_body->etag) {
        simple_hdr(txn, "ETag", "%s\"%s\"",
                      resp_body->enc.proc ? "W/" : "", resp_body->etag);
        if (txn->flags.cors) Access_Control_Expose("ETag");
    }
    if (resp_body->lastmod) {

        resp_body->lastmod = MIN(resp_body->lastmod, now);
        httpdate_gen(datestr, sizeof(datestr), resp_body->lastmod);
        simple_hdr(txn, "Last-Modified", datestr);
    }


    if (resp_body->prefs) {

        const char *prefs[] =
            { "return=minimal", "return=representation", "depth-noroot", NULL };

        comma_list_hdr(txn, "Preference-Applied", prefs, resp_body->prefs);
        if (txn->flags.cors) Access_Control_Expose("Preference-Applied");
    }
    if (resp_body->cmid) {
        simple_hdr(txn, "Cal-Managed-ID", "%s", resp_body->cmid);
        if (txn->flags.cors) Access_Control_Expose("Cal-Managed-ID");
    }
    if (resp_body->type) {
        simple_hdr(txn, "Content-Type", resp_body->type);
        if (resp_body->dispo.fname) {

            const unsigned char *p = (const unsigned char *)resp_body->dispo.fname;
            char *encfname = NULL;
            for (p = (unsigned char *)resp_body->dispo.fname; p && *p; p++) {
                if (*p >= 0x80) {
                    encfname = charset_encode_mimexvalue(resp_body->dispo.fname, NULL);
                    break;
                }
            }
            if (encfname) {
                simple_hdr(txn, "Content-Disposition", "%s; filename*=%s",
                        resp_body->dispo.attach ? "attachment" : "inline",
                        encfname);
            }
            else {
                simple_hdr(txn, "Content-Disposition", "%s; filename=\"%s\"",
                        resp_body->dispo.attach ? "attachment" : "inline",
                        resp_body->dispo.fname);
            }
            free(encfname);
        }
        if (txn->resp_body.enc.proc) {

            comma_list_hdr(txn, "Content-Encoding", ce, txn->resp_body.enc.type);
        }
        if (resp_body->lang) {
            simple_hdr(txn, "Content-Language", resp_body->lang);
        }
        if (resp_body->loc) {
            simple_hdr(txn, "Content-Location", resp_body->loc);
            if (txn->flags.cors) Access_Control_Expose("Content-Location");
        }
        if (resp_body->md5) {
            content_md5_hdr(txn, resp_body->md5);
        }
    }


    switch (code) {
    case HTTP_NO_CONTENT:
    case HTTP_NOT_MODIFIED:

        resp_body->len = 0;
        break;

    case HTTP_PARTIAL:
    case HTTP_BAD_RANGE:
        if (resp_body->range) {
            simple_hdr(txn, "Content-Range", "bytes %lu-%lu/%lu",
                       resp_body->range->first, resp_body->range->last,
                       resp_body->len);


            resp_body->len =
                resp_body->range->last - resp_body->range->first + 1;

            free(resp_body->range);
        }
        else {
            simple_hdr(txn, "Content-Range", "bytes */%lu", resp_body->len);
            resp_body->len = 0;
        }


        GCC_FALLTHROUGH

    default:
        if (txn->flags.te) {

            if (txn->flags.ver == VER_1_1) {

                comma_list_hdr(txn, "Transfer-Encoding", te, txn->flags.te);
            }

            if (txn->flags.trailer & ~TRAILER_PROXY) {

                const char *trailer_hdrs[] = { "Content-MD5", "CTag", NULL };

                comma_list_hdr(txn, "Trailer", trailer_hdrs, txn->flags.trailer);
            }
        }
        else {

            switch (txn->meth) {
            case METH_CONNECT:

                break;

            case METH_HEAD:
                if (!resp_body->len) {


                    break;
                }

                GCC_FALLTHROUGH

            default:
                simple_hdr(txn, "Content-Length", "%lu", resp_body->len);
                break;
            }
        }
    }


    if (resp_body->extra_hdrs) {
        spool_enum_hdrcache(resp_body->extra_hdrs, &write_cachehdr, txn);
    }


    end_resp_headers(txn, code);


  log:

    buf_reset(logbuf);


    buf_printf(logbuf, "%s", txn->conn->clienthost);
    if (httpd_userid) buf_printf(logbuf, " as \"%s\"", httpd_userid);
    if (txn->req_hdrs &&
        (hdr = spool_getheader(txn->req_hdrs, "User-Agent"))) {
        buf_printf(logbuf, " with \"%s\"", hdr[0]);
        if ((hdr = spool_getheader(txn->req_hdrs, "X-Client")))
            buf_printf(logbuf, " by \"%s\"", hdr[0]);
        else if ((hdr = spool_getheader(txn->req_hdrs, "X-Requested-With")))
            buf_printf(logbuf, " by \"%s\"", hdr[0]);
    }


    buf_printf(logbuf, " via SESSIONID=<%s>", session_id());


    buf_appendcstr(logbuf, "; \"");
    if (txn->req_line.meth) {
        buf_printf(logbuf, "%s",
                   txn->flags.override ? "POST" : txn->req_line.meth);
        if (txn->req_line.uri) {
            buf_printf(logbuf, " %s", txn->req_line.uri);
            if (txn->req_line.ver) {
                buf_printf(logbuf, " %s", txn->req_line.ver);
                if (code != HTTP_URI_TOO_LONG && *txn->req_line.buf) {
                    const char *p =
                        txn->req_line.ver + strlen(txn->req_line.ver) + 1;
                    if (*p) buf_printf(logbuf, " %s", p);
                }
            }
        }
    }
    buf_appendcstr(logbuf, "\"");

    if (txn->req_hdrs) {

        sep = " (";

        if (txn->flags.override) {
            buf_printf(logbuf, "%smethod-override=%s", sep, txn->req_line.meth);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "Origin"))) {
            buf_printf(logbuf, "%sorigin=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "Referer"))) {
            buf_printf(logbuf, "%sreferer=%s", sep, hdr[0]);
            sep = "; ";
        }
        if (txn->flags.upgrade &&
            (hdr = spool_getheader(txn->req_hdrs, "Upgrade"))) {
            buf_printf(logbuf, "%supgrade=%s", sep, hdr[0]);
            sep = "; ";
        }
        if (code == HTTP_CONTINUE || code == HTTP_EXPECT_FAILED) {
            hdr = spool_getheader(txn->req_hdrs, "Expect");
            buf_printf(logbuf, "%sexpect=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "Transfer-Encoding"))) {
            buf_printf(logbuf, "%stx-encoding=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "Content-Encoding"))) {
            buf_printf(logbuf, "%scnt-encoding=%s", sep, hdr[0]);
            sep = "; ";
        }
        if (txn->auth_chal.scheme) {
            buf_printf(logbuf, "%sauth=%s", sep, txn->auth_chal.scheme->name);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "Destination"))) {
            buf_printf(logbuf, "%sdestination=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "Lock-Token"))) {
            buf_printf(logbuf, "%slock-token=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "If"))) {
            buf_printf(logbuf, "%sif=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "If-Schedule-Tag-Match"))) {
            buf_printf(logbuf, "%sif-schedule-tag-match=%s", sep, hdr[0]);
            sep = "; ";
        }
        else if ((hdr = spool_getheader(txn->req_hdrs, "If-Match"))) {
            buf_printf(logbuf, "%sif-match=%s", sep, hdr[0]);
            sep = "; ";
        }
        else if ((hdr = spool_getheader(txn->req_hdrs, "If-Unmodified-Since"))) {
            buf_printf(logbuf, "%sif-unmodified-since=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "If-None-Match"))) {
            buf_printf(logbuf, "%sif-none-match=%s", sep, hdr[0]);
            sep = "; ";
        }
        else if ((hdr = spool_getheader(txn->req_hdrs, "If-Modified-Since"))) {
            buf_printf(logbuf, "%sif-modified-since=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, ":type"))) {
            buf_printf(logbuf, "%stype=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, ":token"))) {
            buf_printf(logbuf, "%stoken=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, ":jmap"))) {
            buf_printf(logbuf, "%sjmap=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, ":dblookup"))) {
            buf_printf(logbuf, "%slookup=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "Depth"))) {
            buf_printf(logbuf, "%sdepth=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "Prefer"))) {
            buf_printf(logbuf, "%sprefer=%s", sep, hdr[0]);
            sep = "; ";
        }
        else if ((hdr = spool_getheader(txn->req_hdrs, "Brief"))) {
            buf_printf(logbuf, "%sbrief=%s", sep, hdr[0]);
            sep = "; ";
        }
        if ((hdr = spool_getheader(txn->req_hdrs, "CalDAV-Timezones"))) {
            buf_printf(logbuf, "%scaldav-timezones=%s", sep, hdr[0]);
            sep = "; ";
        }

        if (*sep == ';') buf_appendcstr(logbuf, ")");
    }

    if (txn->flags.redirect) {

        buf_printf(logbuf, " => \"%s %s %s\"",
                   txn->req_line.meth, txn->req_tgt.path, txn->req_line.ver);
    }


    buf_printf(logbuf, " => \"%s\"", http_statusline(txn->flags.ver, code));


    sep = " (";
    if (txn->strm_ctx) {
        buf_printf(logbuf, "%sstream-id=%d", sep,
                   http2_get_streamid(txn->strm_ctx));
        sep = "; ";
    }
    if (code == HTTP_SWITCH_PROT || code == HTTP_UPGRADE) {
        buf_printf(logbuf, "%supgrade=", sep);
        comma_list_body(logbuf, upgrd_tokens, txn->flags.upgrade, NULL);
        sep = "; ";
    }
    if (txn->flags.te) {
        buf_printf(logbuf, "%stx-encoding=", sep);
        comma_list_body(logbuf, te, txn->flags.te, NULL);
        sep = "; ";
    }
    if (txn->resp_body.enc.proc) {
        buf_printf(logbuf, "%scnt-encoding=", sep);
        comma_list_body(logbuf, ce, txn->resp_body.enc.type, NULL);
        sep = "; ";
    }
    if (txn->location) {
        buf_printf(logbuf, "%slocation=%s", sep, txn->location);
        sep = "; ";
    }
    else if (txn->flags.cors) {
        buf_printf(logbuf, "%sallow-origin", sep);
        sep = "; ";
    }
    else if (txn->error.desc) {
        buf_printf(logbuf, "%serror=%s", sep, txn->error.desc);
        sep = "; ";
    }
    if (*sep == ';') buf_appendcstr(logbuf, ")");


    cmdtime_endtimer(&cmdtime, &nettime);
    buf_printf(logbuf, " [timing: cmd=%f net=%f total=%f]",
               cmdtime, nettime, cmdtime + nettime);

    syslog(LOG_INFO, "%s", buf_cstring(logbuf));
}
