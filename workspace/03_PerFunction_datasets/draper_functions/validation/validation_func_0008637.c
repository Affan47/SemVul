gst_mpdparser_parse_mult_seg_base_type_ext (GstMultSegmentBaseType ** pointer,
    xmlNode * a_node, GstMultSegmentBaseType * parent)
{
  xmlNode *cur_node;
  GstMultSegmentBaseType *mult_seg_base_type;
  guint intval;

  gst_mpdparser_free_mult_seg_base_type_ext (*pointer);
  *pointer = mult_seg_base_type = g_slice_new0 (GstMultSegmentBaseType);
  if (mult_seg_base_type == NULL) {
    GST_WARNING ("Allocation of MultipleSegmentBaseType node failed!");
    return;
  }


  if (parent) {
    mult_seg_base_type->duration = parent->duration;
    mult_seg_base_type->startNumber = parent->startNumber;
    mult_seg_base_type->SegmentTimeline =
        gst_mpdparser_clone_segment_timeline (parent->SegmentTimeline);
    mult_seg_base_type->BitstreamSwitching =
        gst_mpdparser_clone_URL (parent->BitstreamSwitching);
  }

  GST_LOG ("attributes of MultipleSegmentBaseType extension:");
  if (gst_mpdparser_get_xml_prop_unsigned_integer (a_node, "duration", 0,
          &intval)) {
    mult_seg_base_type->duration = intval;
  }
  if (gst_mpdparser_get_xml_prop_unsigned_integer (a_node, "startNumber", 1,
          &intval)) {
    mult_seg_base_type->startNumber = intval;
  }

  GST_LOG ("extension of MultipleSegmentBaseType extension:");
  gst_mpdparser_parse_seg_base_type_ext (&mult_seg_base_type->SegBaseType,
      a_node, (parent ? parent->SegBaseType : NULL));


  for (cur_node = a_node->children; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      if (xmlStrcmp (cur_node->name, (xmlChar *) "SegmentTimeline") == 0) {
        if (mult_seg_base_type->SegmentTimeline) {
          gst_mpdparser_free_segment_timeline_node
              (mult_seg_base_type->SegmentTimeline);
        }
        gst_mpdparser_parse_segment_timeline_node
            (&mult_seg_base_type->SegmentTimeline, cur_node);
      } else if (xmlStrcmp (cur_node->name,
              (xmlChar *) "BitstreamSwitching") == 0) {
        if (mult_seg_base_type->BitstreamSwitching) {
          gst_mpdparser_free_url_type_node
              (mult_seg_base_type->BitstreamSwitching);
        }
        gst_mpdparser_parse_url_type_node
            (&mult_seg_base_type->BitstreamSwitching, cur_node);
      }
    }
  }
}
