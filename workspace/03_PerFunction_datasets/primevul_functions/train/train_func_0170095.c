Event_job_data::execute(THD *thd, bool drop)
{
  String sp_sql;
#ifndef NO_EMBEDDED_ACCESS_CHECKS
  Security_context event_sctx, *save_sctx= NULL;
#endif
  List<Item> empty_item_list;
  bool ret= TRUE;

  DBUG_ENTER("Event_job_data::execute");

  thd->reset_for_next_command();


  thd->set_db(dbname.str, dbname.length);

  lex_start(thd);

#ifndef NO_EMBEDDED_ACCESS_CHECKS
  if (event_sctx.change_security_context(thd,
                                         &definer_user, &definer_host,
                                         &dbname, &save_sctx))
  {
    sql_print_error("Event Scheduler: "
                    "[%s].[%s.%s] execution failed, "
                    "failed to authenticate the user.",
                    definer.str, dbname.str, name.str);
    goto end;
  }
#endif

  if (check_access(thd, EVENT_ACL, dbname.str, NULL, NULL, 0, 0))
  {


    sql_print_error("Event Scheduler: "
                    "[%s].[%s.%s] execution failed, "
                    "user no longer has EVENT privilege.",
                    definer.str, dbname.str, name.str);
    goto end;
  }

  if (construct_sp_sql(thd, &sp_sql))
    goto end;


  thd->variables.sql_mode= sql_mode;
  thd->variables.time_zone= time_zone;

  thd->set_query(sp_sql.c_ptr_safe(), sp_sql.length());

  {
    Parser_state parser_state;
    if (parser_state.init(thd, thd->query(), thd->query_length()))
      goto end;

    if (parse_sql(thd, & parser_state, creation_ctx))
    {
      sql_print_error("Event Scheduler: "
                      "%serror during compilation of %s.%s",
                      thd->is_fatal_error ? "fatal " : "",
                      (const char *) dbname.str, (const char *) name.str);
      goto end;
    }
  }

  {
    sp_head *sphead= thd->lex->sphead;

    DBUG_ASSERT(sphead);

    sphead->m_flags|= sp_head::LOG_SLOW_STATEMENTS;
    sphead->m_flags|= sp_head::LOG_GENERAL_LOG;

    sphead->set_info(0, 0, &thd->lex->sp_chistics, sql_mode);
    sphead->set_creation_ctx(creation_ctx);
    sphead->optimize();

    ret= sphead->execute_procedure(thd, &empty_item_list);


  }

end:
  if (drop && !thd->is_fatal_error)
  {


    sql_print_information("Event Scheduler: Dropping %s.%s",
                          (const char *) dbname.str, (const char *) name.str);


    if (construct_drop_event_sql(thd, &sp_sql))
      ret= 1;
    else
    {
      ulong saved_master_access;

      thd->set_query(sp_sql.c_ptr_safe(), sp_sql.length());


      saved_master_access= thd->security_ctx->master_access;
      thd->security_ctx->master_access |= SUPER_ACL;
      bool save_tx_read_only= thd->tx_read_only;
      thd->tx_read_only= false;


      const enum_sql_command sql_command_save= thd->lex->sql_command;
      const bool sql_command_set= WSREP(thd);

      if (sql_command_set)
        thd->lex->sql_command = SQLCOM_DROP_EVENT;

      ret= Events::drop_event(thd, dbname, name, FALSE);

      if (sql_command_set)
      {
        WSREP_TO_ISOLATION_END;
        thd->lex->sql_command = sql_command_save;
      }

      thd->tx_read_only= save_tx_read_only;
      thd->security_ctx->master_access= saved_master_access;
    }
  }
#ifndef NO_EMBEDDED_ACCESS_CHECKS
  if (save_sctx)
    event_sctx.restore_security_context(thd, save_sctx);
#endif
  thd->lex->unit.cleanup();
  thd->end_statement();
  thd->cleanup_after_query();

  thd->reset_query();

  DBUG_PRINT("info", ("EXECUTED %s.%s  ret: %d", dbname.str, name.str, ret));

  DBUG_RETURN(ret);
}
