gst_au_parse_negotiate_srcpad (GstAuParse * auparse, GstCaps * new_caps)
{
  if (auparse->src_caps && gst_caps_is_equal (new_caps, auparse->src_caps)) {
    GST_LOG_OBJECT (auparse, "same caps, nothing to do");
    return;
  }

  gst_caps_replace (&auparse->src_caps, new_caps);
  GST_DEBUG_OBJECT (auparse, "Changing src pad caps to %" GST_PTR_FORMAT,
      auparse->src_caps);
  gst_pad_set_caps (auparse->srcpad, auparse->src_caps);

  return;
}
