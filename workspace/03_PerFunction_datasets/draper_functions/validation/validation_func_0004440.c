test_plugin_info_os_dependant_help (PeasEngine *engine)
{
  PeasPluginInfo *info;
  const gchar *help;

  info = peas_engine_get_plugin_info (engine, "os-dependant-help");

  help = peas_plugin_info_get_help_uri (info);

#ifdef G_OS_WIN32
  g_assert_cmpstr (help, ==, "Windows");
#elif defined(OS_OSX)
  g_assert_cmpstr (help, ==, "MacOS-X");
#else
  g_assert_cmpstr (help, ==, "GNOME");
#endif
}
