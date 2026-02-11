start_wait_request(HTTPContext *c, int is_rtsp)
{
    c->buffer_ptr = c->buffer;
    c->buffer_end = c->buffer + c->buffer_size - 1;

    if (is_rtsp) {
        c->timeout = cur_time + RTSP_REQUEST_TIMEOUT;
        c->state = RTSPSTATE_WAIT_REQUEST;
    } else {
        c->timeout = cur_time + HTTP_REQUEST_TIMEOUT;
        c->state = HTTPSTATE_WAIT_REQUEST;
    }
}
