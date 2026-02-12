EXPORTED void write_body(long code, struct transaction_t *txn,
                         const char *buf, unsigned len)
{
    unsigned outlen = len, offset = 0, last_chunk;
    int do_md5 = (txn->meth == METH_HEAD) ? 0 :
        config_getswitch(IMAPOPT_HTTPCONTENTMD5);
    static MD5_CTX ctx;
    static unsigned char md5[MD5_DIGEST_LENGTH];

    syslog(LOG_DEBUG, "write_body(code = %ld, flags.te = %#x, len = %u)",
           code, txn->flags.te, len);

    if (txn->flags.te & TE_CHUNKED) last_chunk = !(code || len);
    else {

        last_chunk = 1;

        if (len < GZIP_MIN_LEN) {

            txn->resp_body.enc.type = CE_IDENTITY;
            txn->resp_body.enc.proc = NULL;
            txn->flags.te = TE_NONE;
        }
    }


    if (txn->resp_body.enc.proc || txn->flags.te & ~TE_CHUNKED) {
        unsigned flags = 0;

        if (code) flags |= COMPRESS_START;
        if (last_chunk) flags |= COMPRESS_END;

        if (txn->resp_body.enc.proc(txn, flags, buf, len) < 0) {
            fatal("Error while compressing data", EX_SOFTWARE);
        }

        buf = txn->zbuf.s;
        outlen = txn->zbuf.len;
    }

    if (code) {

        if (do_md5) MD5Init(&ctx);

        if (txn->flags.te & ~TE_CHUNKED) {

            txn->flags.te |= TE_CHUNKED;
        }

        if (!txn->flags.te) {


            txn->resp_body.len = outlen;

            if (code == HTTP_PARTIAL) {

                code = parse_ranges(*spool_getheader(txn->req_hdrs, "Range"),
                                    outlen, &txn->resp_body.range);

                switch (code) {
                case HTTP_OK:

                    break;

                case HTTP_PARTIAL:

                    txn->resp_body.len = outlen;

                    if (txn->resp_body.range->next) {

                        multipart_byteranges(txn, buf);
                        return;
                    }
                    else {

                        offset += txn->resp_body.range->first;
                        outlen = txn->resp_body.range->last -
                            txn->resp_body.range->first + 1;
                    }
                    break;

                case HTTP_BAD_RANGE:

                    outlen = 0;
                    break;
                }
            }

            if (outlen && do_md5) {
                MD5Update(&ctx, buf+offset, outlen);
                MD5Final(md5, &ctx);
                txn->resp_body.md5 = md5;
            }
        }
        else if (txn->flags.ver == VER_1_0) {

            txn->flags.conn = CONN_CLOSE;
        }
        else if (do_md5) txn->flags.trailer |= TRAILER_CMD5;

        response_header(code, txn);


        switch (code) {
        case HTTP_CONTINUE:
        case HTTP_SWITCH_PROT:
        case HTTP_PROCESSING:
        case HTTP_NO_CONTENT:
        case HTTP_NOT_MODIFIED:
            return;

        default:
            if (txn->meth == METH_HEAD) return;
        }
    }


    if (txn->flags.ver == VER_2) {

        if (outlen || txn->flags.te) {
            http2_data_chunk(txn, buf + offset, outlen, last_chunk, &ctx);
        }
    }
    else if (txn->flags.te && txn->flags.ver == VER_1_1) {

        if (outlen) {
            syslog(LOG_DEBUG, "write_body: chunk(%d)", outlen);
            prot_printf(httpd_out, "%x\r\n", outlen);
            prot_write(httpd_out, buf, outlen);
            prot_puts(httpd_out, "\r\n");

            if (txn->flags.trailer & TRAILER_CMD5) MD5Update(&ctx, buf, outlen);
        }
        if (last_chunk) {

            syslog(LOG_DEBUG, "write_body: last chunk");
            prot_puts(httpd_out, "0\r\n");


            if (txn->flags.trailer & TRAILER_CMD5) {
                syslog(LOG_DEBUG, "write_body: trailer Content-MD5");
                MD5Final(md5, &ctx);
                content_md5_hdr(txn, md5);
            }
            if ((txn->flags.trailer & TRAILER_CTAG) && txn->resp_body.ctag) {
                syslog(LOG_DEBUG, "write_body: trailer CTag");
                simple_hdr(txn, "CTag", "%s", txn->resp_body.ctag);
            }

            if (txn->flags.trailer != TRAILER_PROXY) {
                syslog(LOG_DEBUG, "write_body: CRLF");
                prot_puts(httpd_out, "\r\n");
            }
        }
    }
    else {

        prot_write(httpd_out, buf + offset, outlen);
    }
}
