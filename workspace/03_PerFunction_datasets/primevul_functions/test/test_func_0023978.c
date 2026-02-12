plugin_ref plugin_lock(THD *thd, plugin_ref ptr)
{
  LEX *lex= thd ? thd->lex : 0;
  plugin_ref rc;
  DBUG_ENTER("plugin_lock");

#ifdef DBUG_OFF


  if (! plugin_dlib(ptr))
  {
    plugin_ref_to_int(ptr)->locks_total++;
    DBUG_RETURN(ptr);
  }
#endif
  mysql_mutex_lock(&LOCK_plugin);
  plugin_ref_to_int(ptr)->locks_total++;
  rc= intern_plugin_lock(lex, ptr);
  mysql_mutex_unlock(&LOCK_plugin);
  DBUG_RETURN(rc);
}
