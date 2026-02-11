preferences_manager_finalize (GObject *object)
{
  PreferencesManager *pref = PREFERENCES_MANAGER(object);
  PreferencesManagerDetails *prefdet;
  prefdet = PREFERENCES_MANAGER_GET_PRIVATE(pref);

  clean_default_settings(prefdet);

  g_free(prefdet->font_name);
  g_free(prefdet->style_name);
  g_object_unref(prefdet->session);
  if (prefdet->session_files){
   g_slist_foreach(prefdet->session_files,  (GFunc) g_free, NULL);
   g_slist_free(prefdet->session_files);
  }

  G_OBJECT_CLASS (preferences_manager_parent_class)->finalize (object);
}
