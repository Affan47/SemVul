gst_video_test_src_getcaps (GstBaseSrc * bsrc)
{
  static GstCaps *capslist = NULL;

  if (!capslist) {
    GstCaps *caps;
    GstStructure *structure;
    int i;

    caps = gst_caps_new_empty ();
    for (i = 0; i < n_fourccs; i++) {
      structure = paint_get_structure (fourcc_list + i);
      gst_structure_set (structure,
          "width", GST_TYPE_INT_RANGE, 1, G_MAXINT,
          "height", GST_TYPE_INT_RANGE, 1, G_MAXINT,
          "framerate", GST_TYPE_FRACTION_RANGE, 0, 1, G_MAXINT, 1, NULL);
      gst_caps_append_structure (caps, structure);
    }

    capslist = caps;
  }

  return gst_caps_copy (capslist);
}
