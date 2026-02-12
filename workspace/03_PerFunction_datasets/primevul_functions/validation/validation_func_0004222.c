connection_handle_read_post_state (request_st * const r)
{
    connection * const con = r->con;
    chunkqueue * const cq = &r->read_queue;
    chunkqueue * const dst_cq = &r->reqbody_queue;

    int is_closed = 0;

    if (r->http_version > HTTP_VERSION_1_1) {

        if (r->h2state >= H2_STATE_HALF_CLOSED_REMOTE)
            is_closed = 1;
    }
    else if (con->is_readable > 0) {
        con->read_idle_ts = log_epoch_secs;

        switch(con->network_read(con, cq, MAX_READ_LIMIT)) {
        case -1:
            connection_set_state_error(r, CON_STATE_ERROR);
            return HANDLER_ERROR;
        case -2:
            is_closed = 1;
            break;
        default:
            break;
        }

        chunkqueue_remove_finished_chunks(cq);
    }


    if (light_btst(r->rqst_htags, HTTP_HEADER_EXPECT)
        && !connection_check_expect_100(r, con))
        return HANDLER_ERROR;

    if (r->http_version > HTTP_VERSION_1_1) {

    }
    else if (r->reqbody_length < 0) {

        handler_t rc = (-1 == r->reqbody_length)
                     ? connection_handle_read_post_chunked(r, cq, dst_cq)
                     : connection_handle_read_body_unknown(r, cq, dst_cq);
        if (HANDLER_GO_ON != rc) return rc;
        chunkqueue_remove_finished_chunks(cq);
    }
    else {
        off_t len = (off_t)r->reqbody_length - dst_cq->bytes_in;
        if (r->reqbody_length <= 64*1024) {

            chunkqueue_steal(dst_cq, cq, len);
        }
        else if (0 !=
                 chunkqueue_steal_with_tempfiles(dst_cq,cq,len,r->conf.errh)) {

            return http_response_reqbody_read_error(r, 500);
        }
        chunkqueue_remove_finished_chunks(cq);
    }

    if (dst_cq->bytes_in == (off_t)r->reqbody_length) {

        r->conf.stream_request_body &= ~FDEVENT_STREAM_REQUEST_POLLIN;
        if (r->state == CON_STATE_READ_POST) {
            connection_set_state(r, CON_STATE_HANDLE_REQUEST);
        }
        return HANDLER_GO_ON;
    }
    else if (is_closed) {
      #if 0
        return http_response_reqbody_read_error(r, 400);
      #endif
        return HANDLER_ERROR;
    }
    else {
        r->conf.stream_request_body |= FDEVENT_STREAM_REQUEST_POLLIN;
        return (r->conf.stream_request_body & FDEVENT_STREAM_REQUEST)
          ? HANDLER_GO_ON
          : HANDLER_WAIT_FOR_EVENT;
    }
}
