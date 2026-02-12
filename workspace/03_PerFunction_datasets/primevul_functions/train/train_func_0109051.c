my_bool STDCALL mysql_stmt_reset(MYSQL_STMT *stmt)
{
  DBUG_ENTER("mysql_stmt_reset");
  DBUG_ASSERT(stmt != 0);
  if (!stmt->mysql)
  {

    set_stmt_error(stmt, CR_SERVER_LOST, unknown_sqlstate, NULL);
    DBUG_RETURN(1);
  }

  DBUG_RETURN(reset_stmt_handle(stmt,
                                RESET_SERVER_SIDE | RESET_LONG_DATA |
                                RESET_CLEAR_ERROR));
}
