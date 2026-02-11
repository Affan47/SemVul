clutter_transform_info_free (gpointer data)
{
  if (data != NULL)
    g_slice_free (ClutterTransformInfo, data);
}
