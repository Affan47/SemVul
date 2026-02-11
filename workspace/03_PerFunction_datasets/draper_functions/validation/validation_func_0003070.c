create_sink (EmpathyGstAudioSink *self)
{
  GstElement *sink;
  const gchar *description;

  description = g_getenv ("EMPATHY_AUDIO_SINK");

  if (description != NULL)
    {
      GError *error = NULL;

      sink = gst_parse_bin_from_description (description, TRUE, &error);
      if (sink == NULL)
        {
          DEBUG ("Failed to create bin %s: %s", description, error->message);
          g_error_free (error);
        }

      return sink;
    }


  sink = gst_element_factory_make ("pulsesink", NULL);
  if (sink == NULL)
    return NULL;

  empathy_audio_set_stream_properties (sink, self->priv->echo_cancel);


  g_object_set (sink,
      "buffer-time", (gint64) 40000,
      "latency-time", (gint64) 10000,
      NULL);

  return sink;
}
