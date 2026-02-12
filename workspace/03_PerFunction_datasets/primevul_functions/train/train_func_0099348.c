release_chunk (GMarkupParseContext *context, GString *str)
{
  GSList *node;
  if (!str)
    return;
  if (str->allocated_len > 256)
    {
      g_string_free (str, TRUE);
      return;
    }
  string_blank (str);
  node = get_list_node (context, str);
  context->spare_chunks = g_slist_concat (node, context->spare_chunks);
}
