qtdemux_tag_add_classification (GstQTDemux * qtdemux, GstTagList * taglist,
    const char *tag, const char *dummy, GNode * node)
{
  int offset;
  char *tag_str = NULL;
  guint8 *entity;
  guint16 table;
  gint len;

  len = QT_UINT32 (node->data);
  if (len <= 20)
    goto short_read;

  offset = 12;
  entity = (guint8 *) node->data + offset;
  if (entity[0] == 0 || entity[1] == 0 || entity[2] == 0 || entity[3] == 0) {
    GST_DEBUG_OBJECT (qtdemux,
        "classification info: %c%c%c%c invalid classification entity",
        entity[0], entity[1], entity[2], entity[3]);
    return;
  }

  offset += 4;
  table = QT_UINT16 ((guint8 *) node->data + offset);


  offset += 4;


  tag_str = g_strdup_printf ("----://%u/%s",
      table, (char *) node->data + offset);


  memcpy (tag_str, entity, 4);
  GST_DEBUG_OBJECT (qtdemux, "classification info: %s", tag_str);

  gst_tag_list_add (taglist, GST_TAG_MERGE_APPEND, tag, tag_str, NULL);

  g_free (tag_str);

  return;


short_read:
  {
    GST_DEBUG_OBJECT (qtdemux, "short read parsing 3GP classification");
    return;
  }
}
