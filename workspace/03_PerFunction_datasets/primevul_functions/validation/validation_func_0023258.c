close_system_tables(THD *thd, Open_tables_backup *backup)
{


  for (TABLE *table= thd->open_tables ; table ; table= table->next)
    table->file->extra(HA_EXTRA_PREPARE_FOR_FORCED_CLOSE);

  close_thread_tables(thd);
  thd->restore_backup_open_tables_state(backup);
}
