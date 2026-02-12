TABLE *open_ltable(THD *thd, TABLE_LIST *table_list, thr_lock_type lock_type,
                   uint lock_flags)
{
  TABLE *table;
  Open_table_context ot_ctx(thd, lock_flags);
  bool error;
  DBUG_ENTER("open_ltable");


  if (table_list->table)
    DBUG_RETURN(table_list->table);


  DBUG_ASSERT(thd->locked_tables_mode < LTM_PRELOCKED);

  THD_STAGE_INFO(thd, stage_opening_tables);
  thd->current_tablenr= 0;

  table_list->required_type= FRMTYPE_TABLE;


  DBUG_ASSERT(table_list->mdl_request.type < MDL_SHARED_UPGRADABLE);

  while ((error= open_table(thd, table_list, &ot_ctx)) &&
         ot_ctx.can_recover_from_failed_open())
  {


    thd->mdl_context.rollback_to_savepoint(ot_ctx.start_of_statement_svp());
    table_list->mdl_request.ticket= 0;
    if (ot_ctx.recover_from_failed_open())
      break;
  }

  if (!error)
  {


    DBUG_ASSERT(table_list->table);
    table= table_list->table;
    if (table->file->ht->db_type == DB_TYPE_MRG_MYISAM)
    {


      my_error(ER_WRONG_OBJECT, MYF(0), table->s->db.str,
               table->s->table_name.str, "BASE TABLE");
      table= 0;
      goto end;

    }

    table_list->lock_type= lock_type;
    table->grant= table_list->grant;
    if (thd->locked_tables_mode)
    {
      if (check_lock_and_start_stmt(thd, thd->lex, table_list))
	table= 0;
    }
    else
    {
      DBUG_ASSERT(thd->lock == 0);
      if ((table->reginfo.lock_type= lock_type) != TL_UNLOCK)
	if (! (thd->lock= mysql_lock_tables(thd, &table_list->table, 1,
                                            lock_flags)))
        {
          table= 0;
        }
    }
  }
  else
    table= 0;

end:
  if (table == NULL)
  {
    if (!thd->in_sub_stmt)
      trans_rollback_stmt(thd);
    close_thread_tables(thd);
  }
  THD_STAGE_INFO(thd, stage_after_opening_tables);

  thd_proc_info(thd, 0);
  DBUG_RETURN(table);
}
