collect_timeout (gchar * sessionid, GstRTSPSession * sess, GstPoolSource * psrc)
{
  gint timeout;
  GTimeVal now;

  g_source_get_current_time ((GSource *) psrc, &now);

  timeout = gst_rtsp_session_next_timeout (sess, &now);
  GST_INFO ("%p: next timeout: %d", sess, timeout);
  if (psrc->timeout == -1 || timeout < psrc->timeout)
    psrc->timeout = timeout;
}
