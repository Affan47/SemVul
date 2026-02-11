plugin_init (GstPlugin * plugin)
{
  if (!gst_element_register (plugin, "osssrc", GST_RANK_SECONDARY,
          GST_TYPE_OSS_SRC) ||
      !gst_element_register (plugin, "osssink", GST_RANK_SECONDARY,
          GST_TYPE_OSSSINK)) {
    return FALSE;
  }

  GST_DEBUG_CATEGORY_INIT (oss_debug, "oss", 0, "OSS elements");

#ifdef ENABLE_NLS
  GST_DEBUG ("binding text domain %s to locale dir %s", GETTEXT_PACKAGE,
      LOCALEDIR);
  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
#endif

  return TRUE;
}
