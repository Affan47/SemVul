int nghttp2_session_close_stream(nghttp2_session *session, int32_t stream_id,
                                 uint32_t error_code) {
  int rv;
  nghttp2_stream *stream;
  nghttp2_mem *mem;
  int is_my_stream_id;

  mem = &session->mem;
  stream = nghttp2_session_get_stream(session, stream_id);

  if (!stream) {
    return NGHTTP2_ERR_INVALID_ARGUMENT;
  }

  DEBUGF("stream: stream(%p)=%d close\n", stream, stream->stream_id);

  if (stream->item) {
    nghttp2_outbound_item *item;

    item = stream->item;

    rv = nghttp2_stream_detach_item(stream);

    if (rv != 0) {
      return rv;
    }


    if (!item->queued && item != session->aob.item) {
      nghttp2_outbound_item_free(item, mem);
      nghttp2_mem_free(mem, item);
    }
  }


  if (session->callbacks.on_stream_close_callback) {
    if (session->callbacks.on_stream_close_callback(
            session, stream_id, error_code, session->user_data) != 0) {

      return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
  }

  is_my_stream_id = nghttp2_session_is_my_stream_id(session, stream_id);


  if ((stream->flags & NGHTTP2_STREAM_FLAG_PUSH)) {
    if (!is_my_stream_id) {
      --session->num_incoming_reserved_streams;
    }
  } else {
    if (is_my_stream_id) {
      --session->num_outgoing_streams;
    } else {
      --session->num_incoming_streams;
    }
  }


  stream->flags |= NGHTTP2_STREAM_FLAG_CLOSED;

  if ((session->opt_flags & NGHTTP2_OPTMASK_NO_CLOSED_STREAMS) == 0 &&
      session->server && !is_my_stream_id &&
      nghttp2_stream_in_dep_tree(stream)) {


    nghttp2_session_keep_closed_stream(session, stream);
  } else {
    rv = nghttp2_session_destroy_stream(session, stream);
    if (rv != 0) {
      return rv;
    }
  }

  return 0;
}
