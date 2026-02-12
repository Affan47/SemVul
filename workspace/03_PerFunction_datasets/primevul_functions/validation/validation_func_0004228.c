connection_write_chunkqueue (connection * const con, chunkqueue * const restrict cq, off_t max_bytes)
{


    con->write_request_ts = log_epoch_secs;

    max_bytes = connection_write_throttle(con, max_bytes);
    if (0 == max_bytes) return 1;

    off_t written = cq->bytes_out;
    int ret;

  #ifdef TCP_CORK
    int corked = 0;
  #endif


    if (cq->first->next) {
        const chunk *c = cq->first;
        while (c->type == MEM_CHUNK && NULL != (c = c->next)) ;
      #ifdef TCP_CORK


        if (NULL != c || con->is_ssl_sock) {
            const int sa_family = sock_addr_get_family(&con->srv_socket->addr);
            if (sa_family == AF_INET || sa_family == AF_INET6) {
                corked = 1;
                (void)setsockopt(con->fd, IPPROTO_TCP, TCP_CORK,
                                 &corked, sizeof(corked));
            }
        }
      #endif
    }

    ret = con->network_write(con, cq, max_bytes);
    if (ret >= 0) {
        ret = chunkqueue_is_empty(cq) ? 0 : 1;
    }

  #ifdef TCP_CORK
    if (corked) {
        corked = 0;
        (void)setsockopt(con->fd, IPPROTO_TCP, TCP_CORK,
                         &corked, sizeof(corked));
    }
  #endif

    written = cq->bytes_out - written;
    con->bytes_written += written;
    con->bytes_written_cur_second += written;
    request_st * const r = &con->request;
    if (r->conf.global_bytes_per_second_cnt_ptr)
        *(r->conf.global_bytes_per_second_cnt_ptr) += written;

    return ret;
}
