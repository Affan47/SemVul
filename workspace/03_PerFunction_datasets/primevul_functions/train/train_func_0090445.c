static int session_handle_frame_size_error(nghttp2_session *session) {


  return nghttp2_session_terminate_session(session, NGHTTP2_FRAME_SIZE_ERROR);
}
