gst_encoding_target_finalize (GstEncodingTarget * target)
{
  GST_DEBUG ("Finalizing");

  if (target->name)
    g_free (target->name);
  if (target->category)
    g_free (target->category);
  if (target->description)
    g_free (target->description);

  g_list_foreach (target->profiles, (GFunc) gst_mini_object_unref, NULL);
  g_list_free (target->profiles);
}
