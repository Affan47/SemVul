gnac_profiles_wavpack_save_profile(gpointer data)
{
  if (!data) return;

  gchar *bitrate = NULL;
  gchar *bits_per_sample = NULL;
  AudioProfileWavpack *profile = (AudioProfileWavpack *) data;

  if (profile->bitrate != -1) {
    bitrate = gnac_profiles_utils_gdouble_to_gchararray(profile->bitrate);
  } else if (profile->bits_per_sample != -1) {
    bits_per_sample = gnac_profiles_utils_gdouble_to_gchararray(
        profile->bits_per_sample);
  }

  gchar *extra_processing = gnac_profiles_utils_gdouble_to_gchararray(
      profile->extra_processing);

  XMLDoc *doc = gnac_profiles_default_save_profile(profile->generic,
      &wavpack_bfi);
  gnac_profiles_xml_engine_add_values(doc,
      "mode", profile->mode,
      "bitrate", bitrate,
      "bits-per-sample", bits_per_sample,
      "extra-processing", extra_processing,
      "joint-stereo-mode", profile->joint_stereo_mode,
      "md5", profile->md5,
      NULL);
  gnac_profiles_xml_engine_save_doc(doc, profile->generic->name);

  gnac_profiles_xml_engine_free_doc_xpath(doc);
  g_free(bitrate);
  g_free(bits_per_sample);
  g_free(extra_processing);
}
