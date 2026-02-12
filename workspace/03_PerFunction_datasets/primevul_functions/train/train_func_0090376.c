int nghttp2_session_on_headers_received(nghttp2_session *session,
                                        nghttp2_frame *frame,
                                        nghttp2_stream *stream) {
  int rv = 0;
  if (frame->hd.stream_id == 0) {
    return session_inflate_handle_invalid_connection(
        session, frame, NGHTTP2_ERR_PROTO, "HEADERS: stream_id == 0");
  }
  if ((stream->shut_flags & NGHTTP2_SHUT_RD)) {


    return session_inflate_handle_invalid_connection(
        session, frame, NGHTTP2_ERR_STREAM_CLOSED, "HEADERS: stream closed");
  }
  if (nghttp2_session_is_my_stream_id(session, frame->hd.stream_id)) {
    if (stream->state == NGHTTP2_STREAM_OPENED) {
      rv = session_call_on_begin_headers(session, frame);
      if (rv != 0) {
        return rv;
      }
      return 0;
    }

    return NGHTTP2_ERR_IGN_HEADER_BLOCK;
  }


  if (stream->state != NGHTTP2_STREAM_CLOSING) {
    rv = session_call_on_begin_headers(session, frame);
    if (rv != 0) {
      return rv;
    }
    return 0;
  }
  return NGHTTP2_ERR_IGN_HEADER_BLOCK;
}
