connection_send_1xx (request_st * const r, connection * const con)
{


    chunkqueue * const cq = con->write_queue;

    buffer * const b = chunkqueue_append_buffer_open(cq);
    buffer_copy_string_len(b, CONST_STR_LEN("HTTP/1.1 "));
    http_status_append(b, r->http_status);
    for (uint32_t i = 0; i < r->resp_headers.used; ++i) {
        const data_string * const ds = (data_string *)r->resp_headers.data[i];

        if (buffer_string_is_empty(&ds->value)) continue;
        if (buffer_string_is_empty(&ds->key)) continue;

        buffer_append_string_len(b, CONST_STR_LEN("\r\n"));
        buffer_append_string_buffer(b, &ds->key);
        buffer_append_string_len(b, CONST_STR_LEN(": "));
        buffer_append_string_buffer(b, &ds->value);
    }
    buffer_append_string_len(b, CONST_STR_LEN("\r\n\r\n"));
    chunkqueue_append_buffer_commit(cq);

    if (con->traffic_limit_reached)
        return 1;

    return connection_write_1xx_info(r, con);
}
