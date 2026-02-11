gst_mixer_volume_changed (GstMixer * mixer,
    GstMixerTrack * track, gint * volumes)
{
  GstStructure *s;
  GstMessage *m;
  GValue l = { 0, };
  GValue v = { 0, };
  gint i;

  g_return_if_fail (mixer != NULL);
  g_return_if_fail (GST_IS_ELEMENT (mixer));
  g_return_if_fail (track != NULL);

  s = gst_structure_new (GST_MIXER_MESSAGE_NAME,
      "type", G_TYPE_STRING, "volume-changed",
      "track", GST_TYPE_MIXER_TRACK, track, NULL);

  g_value_init (&l, GST_TYPE_ARRAY);

  g_value_init (&v, G_TYPE_INT);


  for (i = 0; i < track->num_channels; ++i) {
    g_value_set_int (&v, volumes[i]);
    gst_value_array_append_value (&l, &v);
  }
  g_value_unset (&v);

  gst_structure_set_value (s, "volumes", &l);
  g_value_unset (&l);

  m = gst_message_new_element (GST_OBJECT (mixer), s);
  if (gst_element_post_message (GST_ELEMENT (mixer), m) == FALSE) {
    GST_WARNING ("This element has no bus, therefore no message sent!");
  }
}
