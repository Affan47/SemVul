pb_utils_get_file_extension_from_caps (const GstCaps * caps)
{
  const FormatInfo *info;
  const gchar *ext = NULL;
  GstCaps *stripped_caps;

  g_assert (GST_IS_CAPS (caps));

  stripped_caps = copy_and_clean_caps (caps);

  g_assert (gst_caps_is_fixed (stripped_caps));

  info = find_format_info (stripped_caps);

  if (info && info->ext[0] != '\0') {
    ext = info->ext;
  } else if (info && info->desc == NULL) {
    const GstStructure *s;

    s = gst_caps_get_structure (stripped_caps, 0);


    if (strcmp (info->type, "audio/mpeg") == 0) {
      int version = 0, layer = 3;

      if (gst_structure_get_int (s, "mpegversion", &version)) {
        if (version == 2 || version == 4) {
          ext = "aac";
        } else if (version == 1) {
          gst_structure_get_int (s, "layer", &layer);
          if (layer == 1)
            ext = "mp1";
          else if (layer == 2)
            ext = "mp2";
          else
            ext = "mp3";
        }
      }
    }
  }

  gst_caps_unref (stripped_caps);
  return ext;
}
