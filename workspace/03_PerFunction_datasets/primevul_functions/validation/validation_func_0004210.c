static int connection_handle_read_state(connection * const con)  {

    chunkqueue * const cq = con->read_queue;
    chunk *c = cq->first;
    uint32_t clen = 0;
    uint32_t header_len = 0;
    request_st * const r = &con->request;
    uint8_t keepalive_request_start = 0;
    uint8_t pipelined_request_start = 0;
    uint8_t discard_blank = 0;
    unsigned short hoff[8192];

    if (con->request_count > 1) {
        discard_blank = 1;
        if (con->bytes_read == r->bytes_read_ckpt) {
            keepalive_request_start = 1;
            if (NULL != c) {
                pipelined_request_start = 1;


                con->is_readable = 1;


            }
        }
    }

    do {
        if (NULL == c) continue;
        clen = buffer_string_length(c->mem) - c->offset;
        if (0 == clen) continue;
        if (c->offset > USHRT_MAX)
            chunkqueue_compact_mem_offset(cq);

        hoff[0] = 1;
        hoff[1] = (unsigned short)c->offset;


        header_len = http_header_parse_hoff(c->mem->ptr + c->offset,clen,hoff);


        const uint32_t max_request_field_size=r->conf.max_request_field_size;
        if ((header_len ? header_len : clen) > max_request_field_size
            || hoff[0] >= sizeof(hoff)/sizeof(hoff[0])-1) {
            log_error(r->conf.errh, __FILE__, __LINE__, "%s",
                      "oversized request-header -> sending Status 431");
            r->http_status = 431;
            r->keep_alive = 0;
            connection_set_state(r, CON_STATE_REQUEST_END);
            return 1;
        }

        if (0 != header_len) {
            if (hoff[0] > 1) break;

            if (discard_blank) {
                if (header_len == clen) continue;
                const int ch = c->mem->ptr[c->offset+header_len];
                if (ch != '\r' && ch != '\n') {

                    discard_blank = 0;
                    clen = 0;
                    c = connection_discard_blank_line(cq, header_len);
                    continue;
                }
            }
        }

        if (((unsigned char *)c->mem->ptr)[c->offset] < 32) {


            log_error(r->conf.errh, __FILE__, __LINE__, "%s",
                      "invalid request-line -> sending Status 400");
            r->http_status = 400;
            r->keep_alive = 0;
            connection_set_state(r, CON_STATE_REQUEST_END);
            return 1;
        }
    } while ((c = connection_read_header_more(con, cq, c, clen)));

    if (keepalive_request_start) {
        if (con->bytes_read > r->bytes_read_ckpt) {


            r->start_hp.tv_sec = log_epoch_secs;
            if (r->conf.high_precision_timestamps)
                log_clock_gettime_realtime(&r->start_hp);
        }
        if (pipelined_request_start && c) con->read_idle_ts = log_epoch_secs;
    }

    if (NULL == c) return 0;

  #ifdef __COVERITY__
    if (buffer_string_length(c->mem) < hoff[1]) {
        return 1;
    }
  #endif

    char * const hdrs = c->mem->ptr + hoff[1];

    if (con->request_count > 1) {


        request_reset_ex(r);
    }


    else if (!con->is_ssl_sock && r->conf.h2proto
             && hoff[0] == 2 && hoff[2] == 16
             && hdrs[0]=='P' && hdrs[1]=='R' && hdrs[2]=='I' && hdrs[3]==' ') {
        r->http_version = HTTP_VERSION_2;
        return 0;
    }

    r->rqst_header_len = header_len;
    if (r->conf.log_request_header)
        log_error(r->conf.errh, __FILE__, __LINE__,
          "fd: %d request-len: %d\n%.*s", con->fd,
          (int)header_len, (int)header_len, hdrs);
    http_request_headers_process(r, hdrs, hoff, con->proto_default_port);
    chunkqueue_mark_written(cq, r->rqst_header_len);
    connection_set_state(r, CON_STATE_REQUEST_END);

    if (!con->is_ssl_sock && r->conf.h2proto && 0 == r->http_status
        && h2_check_con_upgrade_h2c(r)) {

        r->conditional_is_valid = (1 << COMP_SERVER_SOCKET)
                                | (1 << COMP_HTTP_REMOTE_IP);

        return 0;
    }

    return 1;
}
