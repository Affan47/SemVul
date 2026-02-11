show_create_trigger(THD *thd, const sp_name *trg_name)
{
  TABLE_LIST *lst= get_trigger_table(thd, trg_name);
  uint num_tables;
  Table_triggers_list *triggers;
  int trigger_idx;
  bool error= TRUE;

  if (!lst)
    return TRUE;

  if (check_table_access(thd, TRIGGER_ACL, lst, FALSE, 1, TRUE))
  {
    my_error(ER_SPECIFIC_ACCESS_DENIED_ERROR, MYF(0), "TRIGGER");
    return TRUE;
  }


  MDL_savepoint mdl_savepoint= thd->mdl_context.mdl_savepoint();


  if (open_tables(thd, &lst, &num_tables,
                  MYSQL_OPEN_FORCE_SHARED_HIGH_PRIO_MDL))
  {
    my_error(ER_TRG_CANT_OPEN_TABLE, MYF(0),
             (const char *) trg_name->m_db.str,
             (const char *) lst->table_name);

    goto exit;


  }

  triggers= lst->table->triggers;

  if (!triggers)
  {
    my_error(ER_TRG_DOES_NOT_EXIST, MYF(0));
    goto exit;
  }

  trigger_idx= triggers->find_trigger_by_name(&trg_name->m_name);

  if (trigger_idx < 0)
  {
    my_error(ER_TRG_CORRUPTED_FILE, MYF(0),
             (const char *) trg_name->m_db.str,
             (const char *) lst->table_name);

    goto exit;
  }

  error= show_create_trigger_impl(thd, triggers, trigger_idx);


exit:
  close_thread_tables(thd);

  thd->mdl_context.rollback_to_savepoint(mdl_savepoint);
  return error;
}
