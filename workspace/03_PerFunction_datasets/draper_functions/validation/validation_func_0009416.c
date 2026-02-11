write_one_tag (const GstTagList * list, const gchar * tag, gpointer user_data)
{
  MyForEach *data = (MyForEach *) user_data;
  GList *comments;
  GList *it;

  comments = gst_tag_to_vorbis_comments (list, tag);

  for (it = comments; it != NULL; it = it->next) {
    gchar *result = it->data;

    data->count++;
    data->data_count += strlen (result);
    data->entries = g_list_prepend (data->entries, result);
  }

  g_list_free (comments);
}
