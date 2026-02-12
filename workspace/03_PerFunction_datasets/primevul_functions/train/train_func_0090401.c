int nghttp2_session_want_read(nghttp2_session *session) {
  size_t num_active_streams;


  if (session->goaway_flags & NGHTTP2_GOAWAY_TERM_SENT) {
    return 0;
  }

  num_active_streams = session_get_num_active_streams(session);


  if (num_active_streams > 0) {
    return 1;
  }


  return (session->goaway_flags &
          (NGHTTP2_GOAWAY_SENT | NGHTTP2_GOAWAY_RECV)) == 0;
}
