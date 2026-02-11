rtp_session_send_rtcp (RTPSession * sess, GstClockTime max_delay)
{
  GstClockTime now;

  if (!sess->callbacks.send_rtcp)
    return;

  now = sess->callbacks.request_time (sess, sess->request_time_user_data);

  rtp_session_request_early_rtcp (sess, now, max_delay);
}
