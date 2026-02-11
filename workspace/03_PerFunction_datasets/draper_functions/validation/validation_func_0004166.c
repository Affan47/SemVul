gst_encoding_profile_get_input_caps (GstEncodingProfile * profile)
{
  GstCaps *out, *tmp;
  GList *ltmp;
  GstStructure *st, *outst;
  GQuark out_name;
  guint i, len;
  const GstCaps *fcaps;

  if (GST_IS_ENCODING_CONTAINER_PROFILE (profile)) {
    GstCaps *res = gst_caps_new_empty ();

    for (ltmp = GST_ENCODING_CONTAINER_PROFILE (profile)->encodingprofiles;
        ltmp; ltmp = ltmp->next) {
      GstEncodingProfile *sprof = (GstEncodingProfile *) ltmp->data;
      gst_caps_merge (res, gst_encoding_profile_get_input_caps (sprof));
    }
    return res;
  }

  fcaps = profile->format;


  if ((profile->restriction == NULL) || gst_caps_is_any (profile->restriction))
    return gst_caps_copy (fcaps);


  outst = gst_caps_get_structure (fcaps, 0);
  out_name = gst_structure_get_name_id (outst);
  tmp = gst_caps_new_empty ();
  len = gst_caps_get_size (profile->restriction);

  for (i = 0; i < len; i++) {
    st = gst_structure_copy (gst_caps_get_structure (profile->restriction, i));
    st->name = out_name;
    gst_caps_append_structure (tmp, st);
  }

  out = gst_caps_intersect (tmp, fcaps);
  gst_caps_unref (tmp);

  return out;
}
