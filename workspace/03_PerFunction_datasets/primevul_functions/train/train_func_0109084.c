static my_bool execute(MYSQL_STMT *stmt, char *packet, ulong length)
{
  MYSQL *mysql= stmt->mysql;
  NET	*net= &mysql->net;
  uchar buff[4  +
             5 ];
  my_bool res;
  DBUG_ENTER("execute");
  DBUG_DUMP("packet", (uchar *) packet, length);

  int4store(buff, stmt->stmt_id);
  buff[4]= (char) stmt->flags;
  int4store(buff+5, 1);

  res= test(cli_advanced_command(mysql, COM_STMT_EXECUTE, buff, sizeof(buff),
                                 (uchar*) packet, length, 1, stmt) ||
            (*mysql->methods->read_query_result)(mysql));
  stmt->affected_rows= mysql->affected_rows;
  stmt->server_status= mysql->server_status;
  stmt->insert_id= mysql->insert_id;
  if (res)
  {


    if (stmt->mysql)
      set_stmt_errmsg(stmt, net);
    DBUG_RETURN(1);
  }
  else if (mysql->status == MYSQL_STATUS_GET_RESULT)
    stmt->mysql->status= MYSQL_STATUS_STATEMENT_GET_RESULT;
  DBUG_RETURN(0);
}
