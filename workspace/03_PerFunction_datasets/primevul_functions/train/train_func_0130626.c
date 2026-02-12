gst_rtsp_source_dispatch_read_get_channel (GPollableInputStream * stream,
    GstRTSPWatch * watch)
{
  gssize count;
  guint8 buffer[1024];
  GError *error = NULL;


  count = g_pollable_input_stream_read_nonblocking (stream, buffer, 1024, NULL,
      &error);
  if (count == 0) {

    goto eof;
  }

  if (count < 0) {
    GST_DEBUG ("%s", error->message);
    if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_WOULD_BLOCK) ||
        g_error_matches (error, G_IO_ERROR, G_IO_ERROR_TIMED_OUT)) {
      g_clear_error (&error);
      goto done;
    }
    g_clear_error (&error);
    goto read_error;
  }


done:
  return TRUE;


eof:
  {
    if (watch->funcs.closed)
      watch->funcs.closed (watch, watch->user_data);


    watch->keep_running = FALSE;

    return FALSE;
  }
read_error:
  {
    if (watch->funcs.error_full)
      watch->funcs.error_full (watch, GST_RTSP_ESYS, &watch->message,
          0, watch->user_data);
    else if (watch->funcs.error)
      watch->funcs.error (watch, GST_RTSP_ESYS, watch->user_data);

    goto eof;
  }
}
