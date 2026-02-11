gst_registry_scan_plugin_file (GstRegistryScanContext * context,
    const gchar * filename, off_t file_size, time_t file_mtime)
{
  gboolean changed = FALSE;
  GstPlugin *newplugin = NULL;

#ifdef G_OS_WIN32

  context->helper_state = REGISTRY_SCAN_HELPER_DISABLED;
#endif


  if (context->helper_state == REGISTRY_SCAN_HELPER_NOT_STARTED) {
    GST_DEBUG ("Starting plugin scanner for file %s", filename);
    context->helper = _priv_gst_plugin_loader_funcs.create (context->registry);
    if (context->helper != NULL)
      context->helper_state = REGISTRY_SCAN_HELPER_RUNNING;
    else {
      GST_WARNING ("Failed starting plugin scanner. Scanning in-process");
      context->helper_state = REGISTRY_SCAN_HELPER_DISABLED;
    }
  }

  if (context->helper_state == REGISTRY_SCAN_HELPER_RUNNING) {
    GST_DEBUG ("Using scan-helper to load plugin %s", filename);
    if (!_priv_gst_plugin_loader_funcs.load (context->helper,
            filename, file_size, file_mtime)) {
      g_warning ("External plugin loader failed. This most likely means that "
          "the plugin loader helper binary was not found or could not be run. "
          "You might need to set the GST_PLUGIN_SCANNER environment variable "
          "if your setup is unusual. This should normally not be required "
          "though.");
      context->helper_state = REGISTRY_SCAN_HELPER_DISABLED;
    }
  }


  if (context->helper_state == REGISTRY_SCAN_HELPER_DISABLED) {


    newplugin = gst_plugin_load_file (filename, NULL);
  }

  if (newplugin) {
    GST_DEBUG_OBJECT (context->registry, "marking new plugin %p as registered",
        newplugin);
    newplugin->registered = TRUE;
    gst_object_unref (newplugin);
    changed = TRUE;
  }
#ifndef GST_DISABLE_REGISTRY
  if (!__registry_reuse_plugin_scanner) {
    clear_scan_context (context);
    context->helper_state = REGISTRY_SCAN_HELPER_NOT_STARTED;
  }
#endif

  return changed;
}
