gconf_database_set_sources (GConfDatabase *db,
                            GConfSources  *sources)
{
  if (db->sources != NULL)
    {
#ifdef HAVE_CORBA


      g_assert_not_reached ();
#endif

      gconf_sources_clear_cache(db->sources);
      gconf_sources_free(db->sources);
    }

  db->sources = sources;

  gconf_sources_set_notify_func (db->sources,
				 (GConfSourceNotifyFunc) source_notify_cb,
				 db);
}
