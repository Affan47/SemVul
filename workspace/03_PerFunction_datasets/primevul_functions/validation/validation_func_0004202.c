connection_revents_err (request_st * const r, connection * const con)
{


    const int revents = (int)con->revents_err;
    con->revents_err = 0;

    if (r->state == CON_STATE_CLOSE)
        con->close_timeout_ts = log_epoch_secs - (HTTP_LINGER_TIMEOUT+1);
    else if (revents & FDEVENT_HUP)
        connection_set_state_error(r, CON_STATE_ERROR);
    else if (revents & FDEVENT_RDHUP) {
        int events = fdevent_fdnode_interest(con->fdn);
        events &= ~(FDEVENT_IN|FDEVENT_RDHUP);
        r->conf.stream_request_body &=
          ~(FDEVENT_STREAM_REQUEST_BUFMIN|FDEVENT_STREAM_REQUEST_POLLIN);
        r->conf.stream_request_body |= FDEVENT_STREAM_REQUEST_POLLRDHUP;
        con->is_readable = 1;
        if (chunkqueue_is_empty(con->read_queue)) r->keep_alive = 0;
        if (r->reqbody_length < -1)
            r->reqbody_length = r->reqbody_queue.bytes_in;
        if (sock_addr_get_family(&con->dst_addr) == AF_UNIX) {

            fdevent_fdnode_event_set(con->srv->ev, con->fdn, events);
        }
        else if (fdevent_is_tcp_half_closed(con->fd)) {


            r->conf.stream_request_body |= FDEVENT_STREAM_REQUEST_TCP_FIN;
            fdevent_fdnode_event_set(con->srv->ev, con->fdn, events);
        }
        else {


            connection_set_state_error(r, CON_STATE_ERROR);
        }
    }
    else if (revents & FDEVENT_ERR)
        connection_set_state_error(r, CON_STATE_ERROR);
    else
        log_error(r->conf.errh, __FILE__, __LINE__,
          "connection closed: poll() -> ??? %d", revents);
}
