int nghttp2_session_add_item(nghttp2_session *session,
                             nghttp2_outbound_item *item) {


  int rv = 0;
  nghttp2_stream *stream;
  nghttp2_frame *frame;

  frame = &item->frame;
  stream = nghttp2_session_get_stream(session, frame->hd.stream_id);

  switch (frame->hd.type) {
  case NGHTTP2_DATA:
    if (!stream) {
      return NGHTTP2_ERR_STREAM_CLOSED;
    }

    if (stream->item) {
      return NGHTTP2_ERR_DATA_EXIST;
    }

    rv = nghttp2_stream_attach_item(stream, item);

    if (rv != 0) {
      return rv;
    }

    return 0;
  case NGHTTP2_HEADERS:


    if (frame->headers.cat == NGHTTP2_HCAT_REQUEST ||
        (stream && stream->state == NGHTTP2_STREAM_RESERVED)) {
      nghttp2_outbound_queue_push(&session->ob_syn, item);
      item->queued = 1;
      return 0;
      ;
    }

    nghttp2_outbound_queue_push(&session->ob_reg, item);
    item->queued = 1;
    return 0;
  case NGHTTP2_SETTINGS:
  case NGHTTP2_PING:
    nghttp2_outbound_queue_push(&session->ob_urgent, item);
    item->queued = 1;
    return 0;
  case NGHTTP2_RST_STREAM:
    if (stream) {
      stream->state = NGHTTP2_STREAM_CLOSING;
    }
    nghttp2_outbound_queue_push(&session->ob_reg, item);
    item->queued = 1;
    return 0;
  case NGHTTP2_PUSH_PROMISE: {
    nghttp2_headers_aux_data *aux_data;
    nghttp2_priority_spec pri_spec;

    aux_data = &item->aux_data.headers;

    if (!stream) {
      return NGHTTP2_ERR_STREAM_CLOSED;
    }

    nghttp2_priority_spec_init(&pri_spec, stream->stream_id,
                               NGHTTP2_DEFAULT_WEIGHT, 0);

    if (!nghttp2_session_open_stream(
            session, frame->push_promise.promised_stream_id,
            NGHTTP2_STREAM_FLAG_NONE, &pri_spec, NGHTTP2_STREAM_RESERVED,
            aux_data->stream_user_data)) {
      return NGHTTP2_ERR_NOMEM;
    }


    nghttp2_outbound_queue_push(&session->ob_reg, item);
    item->queued = 1;

    return 0;
  }
  case NGHTTP2_WINDOW_UPDATE:
    if (stream) {
      stream->window_update_queued = 1;
    } else if (frame->hd.stream_id == 0) {
      session->window_update_queued = 1;
    }
    nghttp2_outbound_queue_push(&session->ob_reg, item);
    item->queued = 1;
    return 0;
  default:
    nghttp2_outbound_queue_push(&session->ob_reg, item);
    item->queued = 1;
    return 0;
  }
}
