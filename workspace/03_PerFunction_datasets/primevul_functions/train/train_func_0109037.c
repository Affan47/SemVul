int STDCALL mysql_stmt_execute(MYSQL_STMT *stmt)
{
  MYSQL *mysql= stmt->mysql;
  DBUG_ENTER("mysql_stmt_execute");

  if (!mysql)
  {

    DBUG_RETURN(1);
  }

  if (reset_stmt_handle(stmt, RESET_STORE_RESULT | RESET_CLEAR_ERROR))
    DBUG_RETURN(1);


  if (mysql->methods->stmt_execute(stmt))
    DBUG_RETURN(1);
  stmt->state= MYSQL_STMT_EXECUTE_DONE;
  if (mysql->field_count)
  {
    reinit_result_set_metadata(stmt);
    prepare_to_fetch_result(stmt);
  }
  DBUG_RETURN(test(stmt->last_errno));
}
