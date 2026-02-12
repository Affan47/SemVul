connection_write_1xx_info (request_st * const r, connection * const con)
{


    chunkqueue * const cq = con->write_queue;
    off_t written = cq->bytes_out;

    int rc = con->network_write(con, cq, MAX_WRITE_LIMIT);

    written = cq->bytes_out - written;
    con->bytes_written += written;
    con->bytes_written_cur_second += written;
    if (r->conf.global_bytes_per_second_cnt_ptr)
        *(r->conf.global_bytes_per_second_cnt_ptr) += written;

    if (rc < 0) {
        connection_set_state_error(r, CON_STATE_ERROR);
        return 0;
    }

    if (!chunkqueue_is_empty(cq)) {
        con->is_writable = 0;
        if (cq == &r->write_queue) {


            con->write_queue = chunkqueue_init(NULL);
            chunkqueue_append_chunkqueue(con->write_queue, cq);
        }
    }

  #if 0


    r->write_queue.bytes_in = r->write_queue.bytes_out = 0;
  #endif

    return 1;
}
