int nghttp2_session_want_write(nghttp2_session *session) {


  if (session->goaway_flags & NGHTTP2_GOAWAY_TERM_SENT) {
    return 0;
  }


  return session->aob.item || nghttp2_outbound_queue_top(&session->ob_urgent) ||
         nghttp2_outbound_queue_top(&session->ob_reg) ||
         (!nghttp2_pq_empty(&session->root.obq) &&
          session->remote_window_size > 0) ||
         (nghttp2_outbound_queue_top(&session->ob_syn) &&
          !session_is_outgoing_concurrent_streams_max(session));
}
