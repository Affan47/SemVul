static void postauth_check_hdrs(struct transaction_t *txn)
{
    const char **hdr;

    if (txn->flags.redirect) return;


    if (allow_cors && (hdr = spool_getheader(txn->req_hdrs, "Origin"))) {
        const char *err = NULL;
        xmlURIPtr uri = parse_uri(METH_UNKNOWN, hdr[0], 0, &err);

        if (uri && uri->scheme && uri->server) {
            int o_https = !strcasecmp(uri->scheme, "https");

            if ((https == o_https) &&
                !strcasecmp(uri->server,
                            *spool_getheader(txn->req_hdrs, ":authority"))) {
                txn->flags.cors = CORS_SIMPLE;
            }
            else {
                struct wildmat *wild;


                assert(!buf_len(&txn->buf));
                buf_printf(&txn->buf, "%s://%s",
                           lcase(uri->scheme), lcase(uri->server));
                if (uri->port &&
                    ((o_https && uri->port != 443) ||
                     (!o_https && uri->port != 80))) {
                    buf_printf(&txn->buf, ":%d", uri->port);
                }


                for (wild = allow_cors; wild->pat; wild++) {
                    if (wildmat(buf_cstring(&txn->buf), wild->pat)) {

                        if (!wild->not) txn->flags.cors = CORS_SIMPLE;
                        break;
                    }
                }
                buf_reset(&txn->buf);
            }
        }
        xmlFreeURI(uri);
    }


    if (txn->zstrm &&
        txn->flags.ver == VER_1_1 &&
        (hdr = spool_getheader(txn->req_hdrs, "TE"))) {
        struct accept *e, *enc = parse_accept(hdr);

        for (e = enc; e && e->token; e++) {
            if (e->qual > 0.0 &&
                (!strcasecmp(e->token, "gzip") ||
                 !strcasecmp(e->token, "x-gzip"))) {
                txn->flags.te = TE_GZIP;
            }
            free(e->token);
        }
        if (enc) free(enc);
    }
    else if ((txn->zstrm || txn->brotli || txn->zstd) &&
             (hdr = spool_getheader(txn->req_hdrs, "Accept-Encoding"))) {
        struct accept *e, *enc = parse_accept(hdr);
        float qual = 0.0;

        for (e = enc; e && e->token; e++) {
            if (e->qual > 0.0 && e->qual >= qual) {
                unsigned ce = CE_IDENTITY;
                encode_proc_t proc = NULL;

                if (txn->zstd && !strcasecmp(e->token, "zstd")) {
                    ce = CE_ZSTD;
                    proc = &zstd_compress;
                }
                else if (txn->brotli && !strcasecmp(e->token, "br")) {
                    ce = CE_BR;
                    proc = &brotli_compress;
                }
                else if (txn->zstrm && (!strcasecmp(e->token, "gzip") ||
                                        !strcasecmp(e->token, "x-gzip"))) {
                    ce = CE_GZIP;
                    proc = &zlib_compress;
                }
                else {

                    e->qual = 0.0;
                }


                if (e->qual > qual || txn->resp_body.enc.type < ce) {
                    txn->resp_body.enc.type = ce;
                    txn->resp_body.enc.proc = proc;
                    qual = e->qual;
                }
            }
            free(e->token);
        }
        if (enc) free(enc);
    }
}
