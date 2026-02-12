connection_transition_h2 (request_st * const h2r, connection * const con)
{
    buffer_copy_string_len(&h2r->target,      CONST_STR_LEN("*"));
    buffer_copy_string_len(&h2r->target_orig, CONST_STR_LEN("*"));
    buffer_copy_string_len(&h2r->uri.path,    CONST_STR_LEN("*"));
    h2r->http_method = HTTP_METHOD_PRI;
    h2r->reqbody_length = -1;
    h2r->conf.stream_request_body |= FDEVENT_STREAM_REQUEST_POLLIN;


    if (h2r->state != CON_STATE_ERROR)
        connection_set_state(h2r, CON_STATE_WRITE);

  #if 0
    con->fdn->handler = connection_handle_fdevent_h2;
  #endif

    if (NULL == con->h2)
        h2_init_con(h2r, con, NULL);
}
