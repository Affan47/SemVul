gst_mpdparser_clone_segment_timeline (GstSegmentTimelineNode * pointer)
{
  GstSegmentTimelineNode *clone = NULL;

  if (pointer) {
    clone = gst_mpdparser_segment_timeline_node_new ();
    if (clone) {
      GList *list;
      for (list = g_queue_peek_head_link (&pointer->S); list; list = g_list_next (list)) {
        GstSNode *s_node;
        s_node = (GstSNode *) list->data;
        if (s_node) {
          g_queue_push_tail (&clone->S,
              gst_mpdparser_clone_s_node (s_node));
        }
      }
    } else {
      GST_WARNING ("Allocation of SegmentTimeline node failed!");
    }
  }

  return clone;
}
