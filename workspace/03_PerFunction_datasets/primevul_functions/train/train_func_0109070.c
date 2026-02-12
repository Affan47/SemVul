int STDCALL mysql_stmt_fetch(MYSQL_STMT *stmt)
{
  int rc;
  uchar *row;
  DBUG_ENTER("mysql_stmt_fetch");

  if ((rc= (*stmt->read_row_func)(stmt, &row)) ||
      ((rc= stmt_fetch_row(stmt, row)) && rc != MYSQL_DATA_TRUNCATED))
  {
    stmt->state= MYSQL_STMT_PREPARE_DONE;
    stmt->read_row_func= (rc == MYSQL_NO_DATA) ?
      stmt_read_row_no_data : stmt_read_row_no_result_set;
  }
  else
  {

    stmt->state= MYSQL_STMT_FETCH_DONE;
  }
  DBUG_RETURN(rc);
}
