int nghttp2_session_on_request_headers_received(nghttp2_session *session,
                                                nghttp2_frame *frame) {
  int rv = 0;
  nghttp2_stream *stream;
  if (frame->hd.stream_id == 0) {
    return session_inflate_handle_invalid_connection(
        session, frame, NGHTTP2_ERR_PROTO, "request HEADERS: stream_id == 0");
  }


  if (!session->server) {
    if (session_detect_idle_stream(session, frame->hd.stream_id)) {
      return session_inflate_handle_invalid_connection(
          session, frame, NGHTTP2_ERR_PROTO,
          "request HEADERS: client received request");
    }

    return NGHTTP2_ERR_IGN_HEADER_BLOCK;
  }

  assert(session->server);

  if (!session_is_new_peer_stream_id(session, frame->hd.stream_id)) {
    if (frame->hd.stream_id == 0 ||
        nghttp2_session_is_my_stream_id(session, frame->hd.stream_id)) {
      return session_inflate_handle_invalid_connection(
          session, frame, NGHTTP2_ERR_PROTO,
          "request HEADERS: invalid stream_id");
    }


    stream = nghttp2_session_get_stream_raw(session, frame->hd.stream_id);
    if (stream && (stream->shut_flags & NGHTTP2_SHUT_RD)) {
      return session_inflate_handle_invalid_connection(
          session, frame, NGHTTP2_ERR_STREAM_CLOSED, "HEADERS: stream closed");
    }

    return NGHTTP2_ERR_IGN_HEADER_BLOCK;
  }
  session->last_recv_stream_id = frame->hd.stream_id;

  if (session_is_incoming_concurrent_streams_max(session)) {
    return session_inflate_handle_invalid_connection(
        session, frame, NGHTTP2_ERR_PROTO,
        "request HEADERS: max concurrent streams exceeded");
  }

  if (!session_allow_incoming_new_stream(session)) {

    return NGHTTP2_ERR_IGN_HEADER_BLOCK;
  }

  if (frame->headers.pri_spec.stream_id == frame->hd.stream_id) {
    return session_inflate_handle_invalid_connection(
        session, frame, NGHTTP2_ERR_PROTO, "request HEADERS: depend on itself");
  }

  if (session_is_incoming_concurrent_streams_pending_max(session)) {
    return session_inflate_handle_invalid_stream(session, frame,
                                                 NGHTTP2_ERR_REFUSED_STREAM);
  }

  stream = nghttp2_session_open_stream(
      session, frame->hd.stream_id, NGHTTP2_STREAM_FLAG_NONE,
      &frame->headers.pri_spec, NGHTTP2_STREAM_OPENING, NULL);
  if (!stream) {
    return NGHTTP2_ERR_NOMEM;
  }

  rv = nghttp2_session_adjust_closed_stream(session);
  if (nghttp2_is_fatal(rv)) {
    return rv;
  }

  session->last_proc_stream_id = session->last_recv_stream_id;

  rv = session_call_on_begin_headers(session, frame);
  if (rv != 0) {
    return rv;
  }
  return 0;
}
