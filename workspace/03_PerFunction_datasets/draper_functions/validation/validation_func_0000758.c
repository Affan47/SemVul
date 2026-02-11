about_to_finish_cb (GstElement * element, gchar * uri[])
{
  if (arg_count < max_count) {
    g_object_set (G_OBJECT (element), "uri", uri[arg_count], NULL);
    arg_count++;
  }
}
