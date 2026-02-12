static void cmdloop(struct http_connection *conn)
{
    struct transaction_t txn;


    memset(&txn, 0, sizeof(struct transaction_t));
    txn.conn = conn;

    if (config_getswitch(IMAPOPT_HTTPALLOWCOMPRESS)) {
        txn.zstrm = zlib_init();
        txn.zstd = zstd_init();
        txn.brotli = brotli_init();
    }


    cmdtime_settimer(1);


    mailbox_set_wait_cb((mailbox_wait_cb_t *) &keepalive_response, &txn);

    do {
        int ret = 0;


        transaction_reset(&txn);


        assert(!open_mailboxes_exist());


        do {

            prot_flush(httpd_out);
            if (backend_current) prot_flush(backend_current->out);


            if (shutdown_file(txn.buf.s, txn.buf.alloc) ||
                (httpd_userid &&
                 userdeny(httpd_userid, config_ident, txn.buf.s, txn.buf.alloc))) {
                txn.error.desc = txn.buf.s;
                txn.flags.conn = CONN_CLOSE;
                ret = HTTP_SHUTDOWN;
                break;
            }

            signals_poll();

        } while (!proxy_check_input(protin, httpd_in, httpd_out,
                                    backend_current ? backend_current->in : NULL,
                                    NULL, 30));


        cmdtime_starttimer();

        if (txn.conn->sess_ctx) {

            http2_input(&txn);
        }
        else if (txn.ws_ctx) {

            ws_input(&txn);
        }
        else if (!ret) {

            http1_input(&txn);
        }

        if (ret == HTTP_SHUTDOWN) {
            syslog(LOG_WARNING,
                   "Shutdown file: \"%s\", closing connection", txn.error.desc);
            protgroup_free(protin);
            shut_down(0);
        }

    } while (!(txn.flags.conn & CONN_CLOSE));


    transaction_free(&txn);
}
