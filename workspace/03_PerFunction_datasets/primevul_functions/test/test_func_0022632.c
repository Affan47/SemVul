Open_table_context::recover_from_failed_open()
{
  bool result= FALSE;
  MDL_deadlock_discovery_repair_handler handler;


  m_thd->push_internal_handler(&handler);


  switch (m_action)
  {
    case OT_BACKOFF_AND_RETRY:
      break;
    case OT_REOPEN_TABLES:
      break;
    case OT_DISCOVER:
      {
        if ((result= lock_table_names(m_thd, m_thd->lex->create_info,
                                      m_failed_table, NULL,
                                      get_timeout(), 0)))
          break;

        tdc_remove_table(m_thd, TDC_RT_REMOVE_ALL, m_failed_table->db,
                         m_failed_table->table_name, FALSE);

        m_thd->get_stmt_da()->clear_warning_info(m_thd->query_id);
        m_thd->clear_error();

        No_such_table_error_handler no_such_table_handler;
        bool open_if_exists= m_failed_table->open_strategy == TABLE_LIST::OPEN_IF_EXISTS;

        if (open_if_exists)
          m_thd->push_internal_handler(&no_such_table_handler);

        result= !tdc_acquire_share(m_thd, m_failed_table,
                                   GTS_TABLE | GTS_FORCE_DISCOVERY | GTS_NOLOCK);
        if (open_if_exists)
        {
          m_thd->pop_internal_handler();
          if (result && no_such_table_handler.safely_trapped_errors())
            result= FALSE;
        }


        m_thd->mdl_context.rollback_to_savepoint(start_of_statement_svp());
        break;
      }
    case OT_REPAIR:
      {
        if ((result= lock_table_names(m_thd, m_thd->lex->create_info,
                                      m_failed_table, NULL,
                                      get_timeout(), 0)))
          break;

        tdc_remove_table(m_thd, TDC_RT_REMOVE_ALL, m_failed_table->db,
                         m_failed_table->table_name, FALSE);

        result= auto_repair_table(m_thd, m_failed_table);


        m_thd->mdl_context.rollback_to_savepoint(start_of_statement_svp());
        break;
      }
    default:
      DBUG_ASSERT(0);
  }
  m_thd->pop_internal_handler();


  m_failed_table= NULL;


  m_has_protection_against_grl= FALSE;

  m_action= OT_NO_ACTION;
  return result;
}
