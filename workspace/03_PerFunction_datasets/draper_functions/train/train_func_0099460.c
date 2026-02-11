gst_tag_list_remove_tag (GstTagList * list, const gchar * tag)
{
  g_return_if_fail (GST_IS_TAG_LIST (list));
  g_return_if_fail (tag != NULL);

  gst_structure_remove_field (GST_TAG_LIST_STRUCTURE (list), tag);
}
