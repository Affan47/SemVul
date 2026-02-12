EXPORTED int check_precond(struct transaction_t *txn,
                           const char *etag, time_t lastmod)
{
    hdrcache_t hdrcache = txn->req_hdrs;
    const char **hdr;
    time_t since = 0;


    if ((hdr = spool_getheader(hdrcache, "If-Match"))) {
        if (!etag_match(hdr, etag)) return HTTP_PRECOND_FAILED;


    }


    else if ((hdr = spool_getheader(hdrcache, "If-Unmodified-Since"))) {
        if (time_from_rfc5322(hdr[0], &since, DATETIME_FULL) < 0)
            return HTTP_BAD_REQUEST;

        if (lastmod > since) return HTTP_PRECOND_FAILED;


    }


    if ((hdr = spool_getheader(hdrcache, "If-None-Match"))) {
        if (etag_match(hdr, etag)) {
            if (txn->meth == METH_GET || txn->meth == METH_HEAD)
                return HTTP_NOT_MODIFIED;
            else
                return HTTP_PRECOND_FAILED;
        }


    }


    else if ((txn->meth == METH_GET || txn->meth == METH_HEAD) &&
             (hdr = spool_getheader(hdrcache, "If-Modified-Since"))) {
        if (time_from_rfc5322(hdr[0], &since, DATETIME_FULL) < 0)
            return HTTP_BAD_REQUEST;

        if (lastmod <= since) return HTTP_NOT_MODIFIED;


    }


    if (txn->flags.ranges &&
        txn->meth == METH_GET && (hdr = spool_getheader(hdrcache, "Range"))) {

        if ((hdr = spool_getheader(hdrcache, "If-Range"))) {
            time_from_rfc5322(hdr[0], &since, DATETIME_FULL);
        }


        if (!hdr || (since && (lastmod <= since)) || !etagcmp(hdr[0], etag))
            return HTTP_PARTIAL;
    }


    return HTTP_OK;
}
