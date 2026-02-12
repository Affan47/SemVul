static int http1_input(struct transaction_t *txn)
{
    struct request_line_t *req_line = &txn->req_line;
    int ignore_empty = 1, ret = 0;

    do {

        syslog(LOG_DEBUG, "read & parse request-line");
        if (!prot_fgets(req_line->buf, MAX_REQ_LINE+1, httpd_in)) {
            txn->error.desc = prot_error(httpd_in);
            if (txn->error.desc && strcmp(txn->error.desc, PROT_EOF_STRING)) {

                syslog(LOG_WARNING, "%s, closing connection", txn->error.desc);
                ret = HTTP_TIMEOUT;
            }
            else {

                syslog(LOG_DEBUG, "client closed connection");
            }

            txn->flags.conn = CONN_CLOSE;
            return ret;
        }


    } while (ignore_empty-- && (strcspn(req_line->buf, "\r\n") == 0));


    ret = parse_request_line(txn);


    if (!ret) {
        ret = http_read_headers(httpd_in, 1 ,
                                &txn->req_hdrs, &txn->error.desc);
    }

    if (ret) {
        txn->flags.conn = CONN_CLOSE;
        goto done;
    }


    ret = examine_request(txn, NULL);
    if (ret) goto done;


    if (txn->flags.ver == VER_1_1) alarm(httpd_keepalive);


    ret = process_request(txn);

  done:

    if (ret) error_response(ret, txn);


    if (!(txn->flags.conn & CONN_CLOSE)) {
        txn->req_body.flags |= BODY_DISCARD;
        if (http_read_req_body(txn)) {
            txn->flags.conn = CONN_CLOSE;
        }
    }

    return 0;
}
