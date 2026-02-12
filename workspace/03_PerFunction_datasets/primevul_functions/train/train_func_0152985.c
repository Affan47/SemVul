static int client_need_auth(struct transaction_t *txn, int sasl_result)
{
    if (httpd_tls_required) {

        const char **hdr;


        if ((hdr = spool_getheader(txn->req_hdrs, "Upgrade")) &&
            stristr(hdr[0], TLS_VERSION)) {


            txn->flags.conn |= CONN_UPGRADE;
            txn->flags.upgrade = UPGRADE_TLS;
            return HTTP_UPGRADE;
        }
        else {

            const char *path = txn->req_uri->path;
            const char *query = URI_QUERY(txn->req_uri);
            struct buf *html = &txn->resp_body.payload;


            hdr = spool_getheader(txn->req_hdrs, ":authority");
            buf_printf(&txn->buf, "https://%s", hdr[0]);
            if (strcmp(path, "*")) {
                buf_appendcstr(&txn->buf, path);
                if (query) buf_printf(&txn->buf, "?%s", query);
            }

            txn->location = buf_cstring(&txn->buf);


            buf_reset(html);
            buf_printf(html, tls_message,
                       buf_cstring(&txn->buf), buf_cstring(&txn->buf));


            txn->resp_body.type = "text/html; charset=utf-8";
            return HTTP_MOVED;
        }
    }
    else {

        if (sasl_result == SASL_CONTINUE)
            txn->error.desc = "Continue authentication exchange";
        else if (sasl_result) txn->error.desc = "Authentication failed";
        else txn->error.desc =
                 "Must authenticate to access the specified target";

        return HTTP_UNAUTHORIZED;
    }
}
