bus_sync_handler (GstBus * bus, GstMessage * message, gpointer data)
{
  GstElement *pipeline = (GstElement *) data;

  switch (GST_MESSAGE_TYPE (message)) {
    case GST_MESSAGE_STATE_CHANGED:

      if (GST_MESSAGE_SRC (message) == GST_OBJECT_CAST (pipeline)) {
        GstState old, new, pending;
        gchar *state_transition_name;

        gst_message_parse_state_changed (message, &old, &new, &pending);

        state_transition_name = g_strdup_printf ("%s_%s",
            gst_element_state_get_name (old), gst_element_state_get_name (new));


        {
          gchar *dump_name = g_strconcat ("gst-launch.", state_transition_name,
              NULL);
          GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS (GST_BIN (pipeline),
              GST_DEBUG_GRAPH_SHOW_ALL, dump_name);
          g_free (dump_name);
        }


        {
          gchar *access_name = g_strconcat (g_get_tmp_dir (), G_DIR_SEPARATOR_S,
              "gst-launch", G_DIR_SEPARATOR_S, state_transition_name, NULL);
          g_file_test (access_name, G_FILE_TEST_EXISTS);
          g_free (access_name);
        }

        g_free (state_transition_name);
      }
    default:
      break;
  }
  return GST_BUS_PASS;
}
