ajp_abort_endpoint(ajp_endpoint_t * ae, int shutdown, jk_logger_t *l)
{
    JK_TRACE_ENTER(l);
    if (shutdown == JK_TRUE && IS_VALID_SOCKET(ae->sd)) {
        if (ae->hard_close) {


            jk_close_socket(ae->sd, l);
        }
        else {
            jk_shutdown_socket(ae->sd, l);
        }
        ae->worker->s->connected--;
    }
    ae->sd = JK_INVALID_SOCKET;
    ae->last_op = JK_AJP13_END_RESPONSE;
    JK_TRACE_EXIT(l);
}
