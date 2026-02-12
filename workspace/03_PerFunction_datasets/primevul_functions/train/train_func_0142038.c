apr_status_t h2_request_end_headers(h2_request *req, apr_pool_t *pool, int eos, size_t raw_bytes)
{
    const char *s;


    if (!req->authority) {
        const char *host = apr_table_get(req->headers, "Host");
        if (!host) {
            return APR_BADARG;
        }
        req->authority = host;
    }
    else {
        apr_table_setn(req->headers, "Host", req->authority);
    }

    s = apr_table_get(req->headers, "Content-Length");
    if (!s) {


        if (!eos) {


            req->chunked = 1;
            apr_table_mergen(req->headers, "Transfer-Encoding", "chunked");
        }
        else if (apr_table_get(req->headers, "Content-Type")) {


            apr_table_setn(req->headers, "Content-Length", "0");
        }
    }
    req->raw_bytes += raw_bytes;

    return APR_SUCCESS;
}
