static int session_predicate_request_headers_send(nghttp2_session *session,
                                                  nghttp2_outbound_item *item) {
  if (item->aux_data.headers.canceled) {
    return NGHTTP2_ERR_STREAM_CLOSING;
  }


  if ((session->goaway_flags & NGHTTP2_GOAWAY_RECV) ||
      session_is_closing(session)) {
    return NGHTTP2_ERR_START_STREAM_NOT_ALLOWED;
  }
  return 0;
}
