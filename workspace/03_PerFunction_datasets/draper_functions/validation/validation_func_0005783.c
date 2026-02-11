event_loop (GstElement * bin, GstClockTime start)
{
  GstBus *bus;
  GstMessage *msg = NULL;
  gboolean running = TRUE;

  bus = gst_element_get_bus (bin);

  while (running) {
    msg = gst_bus_poll (bus,
        GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR | GST_MESSAGE_WARNING,
        -1);

    switch (GST_MESSAGE_TYPE (msg)) {
      case GST_MESSAGE_STATE_CHANGED:
        if (GST_MESSAGE_SRC (msg) == (GstObject *) bin) {
          GstState old_state, new_state;
          GstClockTime end;

          gst_message_parse_state_changed (msg, &old_state, &new_state, NULL);

          end = gst_util_get_timestamp ();
          g_print ("%" GST_TIME_FORMAT " state change on the bin: %s -> %s\n",
              GST_TIME_ARGS (end - start),
              gst_element_state_get_name (old_state),
              gst_element_state_get_name (new_state));

          if (old_state == GST_STATE_READY && new_state == GST_STATE_PAUSED) {
            running = FALSE;
          }
        }
        break;
      case GST_MESSAGE_WARNING:{
        GError *err = NULL;
        gchar *dbg = NULL;

        gst_message_parse_warning (msg, &err, &dbg);
        GST_WARNING_OBJECT (GST_MESSAGE_SRC (msg), "%s (%s)", err->message,
            (dbg ? dbg : "no details"));
        g_error_free (err);
        g_free (dbg);
        break;
      }
      case GST_MESSAGE_ERROR:{
        GError *err = NULL;
        gchar *dbg = NULL;

        gst_message_parse_error (msg, &err, &dbg);
        GST_ERROR_OBJECT (GST_MESSAGE_SRC (msg), "%s (%s)", err->message,
            (dbg ? dbg : "no details"));
        g_error_free (err);
        g_free (dbg);
        running = FALSE;
        break;
      }
      default:
        break;
    }
    gst_message_unref (msg);
  }
  gst_object_unref (bus);
}
