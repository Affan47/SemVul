bool mysql_install_plugin(THD *thd, const LEX_STRING *name,
                          const LEX_STRING *dl_arg)
{
  TABLE_LIST tables;
  TABLE *table;
  LEX_STRING dl= *dl_arg;
  bool error;
  int argc=orig_argc;
  char **argv=orig_argv;
  unsigned long event_class_mask[MYSQL_AUDIT_CLASS_MASK_SIZE] =
  { MYSQL_AUDIT_GENERAL_CLASSMASK };
  DBUG_ENTER("mysql_install_plugin");

  tables.init_one_table("mysql", 5, "plugin", 6, "plugin", TL_WRITE);
  if (!opt_noacl && check_table_access(thd, INSERT_ACL, &tables, FALSE, 1, FALSE))
    DBUG_RETURN(TRUE);
  WSREP_TO_ISOLATION_BEGIN(WSREP_MYSQL_DB, NULL, NULL);


  if (! (table = open_ltable(thd, &tables, TL_WRITE,
                             MYSQL_LOCK_IGNORE_TIMEOUT)))
    DBUG_RETURN(TRUE);

  if (my_load_defaults(MYSQL_CONFIG_NAME, load_default_groups, &argc, &argv, NULL))
  {
    report_error(REPORT_TO_USER, ER_PLUGIN_IS_NOT_LOADED, name->str);
    DBUG_RETURN(TRUE);
  }


  if (mysql_audit_general_enabled())
    mysql_audit_acquire_plugins(thd, event_class_mask);

  mysql_mutex_lock(&LOCK_plugin);
  error= plugin_add(thd->mem_root, name, &dl, REPORT_TO_USER);
  if (error)
    goto err;

  if (name->str)
    error= finalize_install(thd, table, name, &argc, argv);
  else
  {
    st_plugin_dl *plugin_dl= plugin_dl_find(&dl);
    struct st_maria_plugin *plugin;
    for (plugin= plugin_dl->plugins; plugin->info; plugin++)
    {
      LEX_STRING str= { const_cast<char*>(plugin->name), strlen(plugin->name) };
      error|= finalize_install(thd, table, &str, &argc, argv);
    }
  }

  if (error)
  {
    reap_needed= true;
    reap_plugins();
  }
err:
  global_plugin_version++;
  mysql_mutex_unlock(&LOCK_plugin);
  if (argv)
    free_defaults(argv);
  DBUG_RETURN(error);

WSREP_ERROR_LABEL:
  DBUG_RETURN(TRUE);
}
