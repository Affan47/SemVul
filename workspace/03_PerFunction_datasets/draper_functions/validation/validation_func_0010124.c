gst_debug_print_object (gpointer ptr)
{
  GObject *object = (GObject *) ptr;

#ifdef unused


  {
    int ret;

    ret = madvise ((void *) ((unsigned long) ptr & (~0xfff)), 4096, 0);
    if (ret == -1 && errno == ENOMEM) {
      buffer = g_strdup_printf ("%p (unmapped memory)", ptr);
    }
  }
#endif


  if (object == NULL) {
    return g_strdup ("(NULL)");
  }
  if (*(GType *) ptr == GST_TYPE_CAPS) {
    return gst_caps_to_string ((const GstCaps *) ptr);
  }
  if (*(GType *) ptr == GST_TYPE_STRUCTURE) {
    return gst_info_structure_to_string ((const GstStructure *) ptr);
  }
  if (*(GType *) ptr == GST_TYPE_CAPS_FEATURES) {
    return gst_caps_features_to_string ((const GstCapsFeatures *) ptr);
  }
  if (*(GType *) ptr == GST_TYPE_TAG_LIST) {
    gchar *str = gst_tag_list_to_string ((GstTagList *) ptr);
    if (G_UNLIKELY (pretty_tags))
      return prettify_structure_string (str);
    else
      return str;
  }
  if (*(GType *) ptr == GST_TYPE_DATE_TIME) {
    return __gst_date_time_serialize ((GstDateTime *) ptr, TRUE);
  }
  if (GST_IS_BUFFER (ptr)) {
    return gst_info_describe_buffer (GST_BUFFER_CAST (ptr));
  }
#ifdef USE_POISONING
  if (*(guint32 *) ptr == 0xffffffff) {
    return g_strdup_printf ("<poisoned@%p>", ptr);
  }
#endif
  if (GST_IS_PAD (object) && GST_OBJECT_NAME (object)) {
    return g_strdup_printf ("<%s:%s>", GST_DEBUG_PAD_NAME (object));
  }
  if (GST_IS_OBJECT (object) && GST_OBJECT_NAME (object)) {
    return g_strdup_printf ("<%s>", GST_OBJECT_NAME (object));
  }
  if (G_IS_OBJECT (object)) {
    return g_strdup_printf ("<%s@%p>", G_OBJECT_TYPE_NAME (object), object);
  }
  if (GST_IS_MESSAGE (object)) {
    return gst_info_describe_message (GST_MESSAGE_CAST (object));
  }
  if (GST_IS_QUERY (object)) {
    return gst_info_describe_query (GST_QUERY_CAST (object));
  }
  if (GST_IS_EVENT (object)) {
    return gst_info_describe_event (GST_EVENT_CAST (object));
  }
  if (GST_IS_CONTEXT (object)) {
    GstContext *context = GST_CONTEXT_CAST (object);
    gchar *s, *ret;
    const gchar *type;
    const GstStructure *structure;

    type = gst_context_get_context_type (context);
    structure = gst_context_get_structure (context);

    s = gst_info_structure_to_string (structure);

    ret = g_strdup_printf ("context '%s'='%s'", type, s);
    g_free (s);
    return ret;
  }

  return g_strdup_printf ("%p", ptr);
}
