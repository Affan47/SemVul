ajp_handle_cping_cpong(ajp_endpoint_t * ae, int timeout, jk_logger_t *l)
{
    int i;
    int cmd;
    jk_msg_buf_t *msg;

    JK_TRACE_ENTER(l);

    ae->last_errno = 0;
    msg = jk_b_new(&ae->pool);
    if (!msg) {
        jk_log(l, JK_LOG_ERROR,
               "Failed allocating AJP message");
        JK_TRACE_EXIT(l);
        return JK_FALSE;
    }
    if (jk_b_set_buffer_size(msg, 16)) {
        jk_log(l, JK_LOG_ERROR,
               "Failed allocating AJP message buffer");
        JK_TRACE_EXIT(l);
        return JK_FALSE;
    }
    jk_b_reset(msg);
    jk_b_append_byte(msg, AJP13_CPING_REQUEST);


    if (ajp_connection_tcp_send_message(ae, msg, l) != JK_TRUE) {
        jk_log(l, JK_LOG_INFO,
               "can't send cping query");
        JK_TRACE_EXIT(l);
        return JK_FALSE;
    }

    for (i = 0; i < 2; i++) {


        if (jk_is_input_event(ae->sd, timeout, l) == JK_FALSE) {
            ae->last_errno = errno;
            jk_log(l, JK_LOG_INFO, "timeout in reply cpong");


            ajp_abort_endpoint(ae, JK_TRUE, l);
            JK_TRACE_EXIT(l);
            return JK_FALSE;
        }


        if (ajp_connection_tcp_get_message(ae, msg, l) != JK_TRUE) {
            jk_log(l, JK_LOG_INFO,
                   "awaited reply cpong, not received");
            JK_TRACE_EXIT(l);
            return JK_FALSE;
        }

        if ((cmd = jk_b_get_byte(msg)) != AJP13_CPONG_REPLY) {


            if (i || ae->last_op == JK_AJP13_END_RESPONSE ||
                     cmd < JK_AJP13_SEND_BODY_CHUNK ||
                     cmd > AJP13_CPONG_REPLY) {
                jk_log(l, JK_LOG_WARNING,
                       "awaited reply cpong, received %d instead. "
                       "Closing connection",
                       cmd);


                ajp_abort_endpoint(ae, JK_TRUE, l);
                JK_TRACE_EXIT(l);
                return JK_FALSE;
            }
            else {
                jk_log(l, JK_LOG_INFO,
                       "awaited reply cpong, received %d instead. "
                       "Retrying next packet",
                       cmd);

            }
        }
        else {
            ae->last_op = AJP13_CPONG_REPLY;


            break;
        }
    }
    JK_TRACE_EXIT(l);
    return JK_TRUE;
}
