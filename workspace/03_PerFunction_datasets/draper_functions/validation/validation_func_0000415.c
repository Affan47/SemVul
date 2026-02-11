gst_encoding_target_finalize (GObject * object)
{
  GstEncodingTarget *target = (GstEncodingTarget *) object;

  GST_DEBUG ("Finalizing");

  if (target->name)
    g_free (target->name);
  if (target->category)
    g_free (target->category);
  if (target->description)
    g_free (target->description);

  g_list_foreach (target->profiles, (GFunc) g_object_unref, NULL);
  g_list_free (target->profiles);
}
