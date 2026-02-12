mysql_stmt_prepare(MYSQL_STMT *stmt, const char *query, ulong length)
{
  MYSQL *mysql= stmt->mysql;
  DBUG_ENTER("mysql_stmt_prepare");

  if (!mysql)
  {

    set_stmt_error(stmt, CR_SERVER_LOST, unknown_sqlstate, NULL);
    DBUG_RETURN(1);
  }


  stmt->last_errno= 0;
  stmt->last_error[0]= '\0';

  if ((int) stmt->state > (int) MYSQL_STMT_INIT_DONE)
  {

    uchar buff[MYSQL_STMT_HEADER];

    if (reset_stmt_handle(stmt, RESET_LONG_DATA | RESET_STORE_RESULT))
      DBUG_RETURN(1);


    stmt->bind_param_done= stmt->bind_result_done= FALSE;
    stmt->param_count= stmt->field_count= 0;
    free_root(&stmt->mem_root, MYF(MY_KEEP_PREALLOC));
    free_root(&stmt->extension->fields_mem_root, MYF(0));

    int4store(buff, stmt->stmt_id);


    stmt->state= MYSQL_STMT_INIT_DONE;
    if (stmt_command(mysql, COM_STMT_CLOSE, buff, 4, stmt))
    {
      set_stmt_errmsg(stmt, &mysql->net);
      DBUG_RETURN(1);
    }
  }

  if (stmt_command(mysql, COM_STMT_PREPARE, (const uchar*) query, length, stmt))
  {
    set_stmt_errmsg(stmt, &mysql->net);
    DBUG_RETURN(1);
  }

  if ((*mysql->methods->read_prepare_result)(mysql, stmt))
  {
    set_stmt_errmsg(stmt, &mysql->net);
    DBUG_RETURN(1);
  }


  if (!(stmt->params= (MYSQL_BIND *) alloc_root(&stmt->mem_root,
						sizeof(MYSQL_BIND)*
                                                (stmt->param_count +
                                                 stmt->field_count))))
  {
    set_stmt_error(stmt, CR_OUT_OF_MEMORY, unknown_sqlstate, NULL);
    DBUG_RETURN(1);
  }
  stmt->bind= stmt->params + stmt->param_count;
  stmt->state= MYSQL_STMT_PREPARE_DONE;
  DBUG_PRINT("info", ("Parameter count: %u", stmt->param_count));
  DBUG_RETURN(0);
}
