EXPORTED int meth_options(struct transaction_t *txn, void *params)
{
    parse_path_t parse_path = (parse_path_t) params;
    int r, i;


    txn->flags.cc |= CC_NOCACHE;


    txn->flags.vary = 0;


    if (!strcmp(txn->req_uri->path, "*")) {
        for (i = 0; http_namespaces[i]; i++) {
            if (http_namespaces[i]->enabled)
                txn->req_tgt.allow |= http_namespaces[i]->allow;
        }

        if (ws_enabled() && (txn->flags.ver == VER_2)) {

            txn->req_tgt.allow |= ALLOW_CONNECT;
        }
    }
    else {
        if (parse_path) {

            r = parse_path(txn->req_uri->path, &txn->req_tgt, &txn->error.desc);
            if (r) return r;
        }
        else if (!strcmp(txn->req_uri->path, "/") &&
                 ws_enabled() && (txn->flags.ver == VER_2)) {

            txn->req_tgt.allow |= ALLOW_CONNECT;
        }

        if (txn->flags.cors) {
            const char **hdr =
                spool_getheader(txn->req_hdrs, "Access-Control-Request-Method");

            if (hdr) {

                unsigned meth;

                txn->flags.cors = CORS_PREFLIGHT;


                for (meth = 0; (meth < METH_UNKNOWN) &&
                         strcmp(http_methods[meth].name, hdr[0]); meth++);

                if (meth == METH_UNKNOWN) txn->flags.cors = 0;
                else {

                    if (!txn->req_tgt.namespace->methods[meth].proc)
                        txn->flags.cors = 0;
                }
            }
        }
    }

    response_header(HTTP_OK, txn);
    return 0;
}
