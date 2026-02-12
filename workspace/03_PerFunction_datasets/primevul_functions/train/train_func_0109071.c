my_bool STDCALL mysql_stmt_free_result(MYSQL_STMT *stmt)
{
  DBUG_ENTER("mysql_stmt_free_result");


  DBUG_RETURN(reset_stmt_handle(stmt, RESET_LONG_DATA | RESET_STORE_RESULT |
                                RESET_CLEAR_ERROR));
}
