static int check_namespace(struct transaction_t *txn)
{
    int i;
    const char **hdr, *query = URI_QUERY(txn->req_uri);
    const struct namespace_t *namespace;
    const struct method_t *meth_t;


    for (i = 0; http_namespaces[i]; i++) {
        const char *path = txn->req_uri->path;
        size_t len;


        if (!http_namespaces[i]->enabled) continue;


        if (http_namespaces[i]->well_known) {
            len = strlen(http_namespaces[i]->well_known);
            if (!strncmp(path, http_namespaces[i]->well_known, len) &&
                (!path[len] || path[len] == '/')) {

                hdr = spool_getheader(txn->req_hdrs, ":authority");
                buf_reset(&txn->buf);
                buf_printf(&txn->buf, "%s://%s",
                           https ? "https" : "http", hdr[0]);
                buf_appendcstr(&txn->buf, http_namespaces[i]->prefix);
                buf_appendcstr(&txn->buf, path + len);
                if (query) buf_printf(&txn->buf, "?%s", query);
                txn->location = buf_cstring(&txn->buf);

                return HTTP_MOVED;
            }
        }


        len = strlen(http_namespaces[i]->prefix);
        if (!strncmp(path, http_namespaces[i]->prefix, len) &&
            (!path[len] || (path[len] == '/') || !strcmp(path, "*"))) {
            break;
        }
    }
    if ((namespace = http_namespaces[i])) {
        txn->req_tgt.namespace = namespace;
        txn->req_tgt.allow = namespace->allow;


        meth_t = &namespace->methods[txn->meth];
        if (!meth_t->proc) return HTTP_NOT_ALLOWED;


        else if ((http_methods[txn->meth].flags & METH_NOBODY) &&
                 (txn->req_body.framing != FRAMING_LENGTH ||

                  txn->req_body.len)) {
            return HTTP_BAD_MEDIATYPE;
        }
    } else {

        return HTTP_SERVER_ERROR;
    }


    if (namespace->auth_schemes) {
        avail_auth_schemes = (namespace->auth_schemes & avail_auth_schemes);


        if ((namespace->auth_schemes & AUTH_BEARER) && namespace->bearer) {
            avail_auth_schemes |= AUTH_BEARER;
        }
    }

    return 0;
}
