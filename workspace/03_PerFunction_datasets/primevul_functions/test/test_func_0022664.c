Locked_tables_list::unlock_locked_table(THD *thd, MDL_ticket *mdl_ticket)
{


  if (thd->locked_tables_mode != LTM_LOCK_TABLES)
    return;

  if (mdl_ticket)
  {


    thd->mdl_context.release_all_locks_for_name(mdl_ticket);
  }

  if (thd->lock->table_count == 0)
    unlock_locked_tables(thd);
}
