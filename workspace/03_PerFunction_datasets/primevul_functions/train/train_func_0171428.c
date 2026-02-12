int ha_start_consistent_snapshot(THD *thd)
{
  bool err, warn= true;


  mysql_mutex_lock(&LOCK_commit_ordered);
  err= plugin_foreach(thd, snapshot_handlerton, MYSQL_STORAGE_ENGINE_PLUGIN, &warn);
  mysql_mutex_unlock(&LOCK_commit_ordered);

  if (err)
  {
    ha_rollback_trans(thd, true);
    return 1;
  }


  if (warn)
    push_warning(thd, Sql_condition::WARN_LEVEL_WARN, ER_UNKNOWN_ERROR,
                 "This MariaDB server does not support any "
                 "consistent-read capable storage engine");
  return 0;
}
