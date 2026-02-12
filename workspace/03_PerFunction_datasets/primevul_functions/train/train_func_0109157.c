mysql_stmt_send_long_data(MYSQL_STMT *stmt, uint param_number,
		     const char *data, ulong length)
{
  MYSQL_BIND *param;
  DBUG_ENTER("mysql_stmt_send_long_data");
  DBUG_ASSERT(stmt != 0);
  DBUG_PRINT("enter",("param no: %d  data: 0x%lx, length : %ld",
		      param_number, (long) data, length));


  if (param_number >= stmt->param_count)
  {
    set_stmt_error(stmt, CR_INVALID_PARAMETER_NO, unknown_sqlstate, NULL);
    DBUG_RETURN(1);
  }

  param= stmt->params+param_number;
  if (!IS_LONGDATA(param->buffer_type))
  {

    strmov(stmt->sqlstate, unknown_sqlstate);
    sprintf(stmt->last_error, ER(stmt->last_errno= CR_INVALID_BUFFER_USE),
	    param->param_number);
    DBUG_RETURN(1);
  }


  if (length || param->long_data_used == 0)
  {
    MYSQL *mysql= stmt->mysql;

    uchar buff[MYSQL_LONG_DATA_HEADER];

    int4store(buff, stmt->stmt_id);
    int2store(buff + 4, param_number);
    param->long_data_used= 1;


    if ((*mysql->methods->advanced_command)(mysql, COM_STMT_SEND_LONG_DATA,
                                            buff, sizeof(buff), (uchar*) data,
                                            length, 1, stmt))
    {


      if (stmt->mysql)
        set_stmt_errmsg(stmt, &mysql->net);
      DBUG_RETURN(1);
    }
  }
  DBUG_RETURN(0);
}
