bool close_cached_tables(THD *thd, TABLE_LIST *tables,
                         bool wait_for_refresh, ulong timeout)
{
  bool result= FALSE;
  struct timespec abstime;
  tdc_version_t refresh_version;
  DBUG_ENTER("close_cached_tables");
  DBUG_ASSERT(thd || (!wait_for_refresh && !tables));

  refresh_version= tdc_increment_refresh_version();

  if (!tables)
  {


    kill_delayed_threads();


    tc_purge(true);

    tdc_purge(true);
  }
  else
  {
    bool found=0;
    for (TABLE_LIST *table= tables; table; table= table->next_local)
    {

      found|= tdc_remove_table(thd, TDC_RT_REMOVE_UNUSED, table->db,
                               table->table_name, TRUE);
    }
    if (!found)
      wait_for_refresh=0;
  }

  DBUG_PRINT("info", ("open table definitions: %d",
                      (int) tdc_records()));

  if (!wait_for_refresh)
    DBUG_RETURN(result);

  if (thd->locked_tables_mode)
  {


    TABLE_LIST *tables_to_reopen= (tables ? tables :
                                  thd->locked_tables_list.locked_tables());


    mysql_ha_flush_tables(thd, tables_to_reopen);

    for (TABLE_LIST *table_list= tables_to_reopen; table_list;
         table_list= table_list->next_global)
    {
      int err;

      TABLE *table= find_table_for_mdl_upgrade(thd, table_list->db,
                                               table_list->table_name, &err);


      if (! table)
        continue;

      if (wait_while_table_is_used(thd, table,
                                   HA_EXTRA_PREPARE_FOR_FORCED_CLOSE))
      {
        result= TRUE;
        goto err_with_reopen;
      }
      close_all_tables_for_name(thd, table->s, HA_EXTRA_NOT_USED, NULL);
    }
  }


  DBUG_PRINT("info", ("Waiting for other threads to close their open tables"));


  mysql_ha_flush(thd);
  DEBUG_SYNC(thd, "after_flush_unlock");

  if (!tables)
  {
    int r= 0;
    close_cached_tables_arg argument;
    argument.refresh_version= refresh_version;
    set_timespec(abstime, timeout);

    while (!thd->killed &&
           (r= tdc_iterate(thd,
                           (my_hash_walk_action) close_cached_tables_callback,
                           &argument)) == 1 &&
           !argument.element->share->wait_for_old_version(thd, &abstime,
                                    MDL_wait_for_subgraph::DEADLOCK_WEIGHT_DDL))
      ;

    if (r)
      result= TRUE;
  }
  else
  {
    for (TABLE_LIST *table= tables; table; table= table->next_local)
    {
      if (thd->killed)
        break;
      if (tdc_wait_for_old_version(thd, table->db, table->table_name, timeout,
                                   MDL_wait_for_subgraph::DEADLOCK_WEIGHT_DDL,
                                   refresh_version))
      {
        result= TRUE;
        break;
      }
    }
  }

err_with_reopen:
  if (thd->locked_tables_mode)
  {


    if (thd->locked_tables_list.reopen_tables(thd, false))
      result= true;


    for (TABLE *tab= thd->open_tables; tab; tab= tab->next)
      tab->mdl_ticket->downgrade_lock(MDL_SHARED_NO_READ_WRITE);
  }
  DBUG_RETURN(result);
}
