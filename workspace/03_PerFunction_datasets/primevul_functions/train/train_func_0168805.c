void STDCALL mysql_close_slow_part(MYSQL *mysql)
{

  if (mysql->net.vio != 0)
  {
    free_old_query(mysql);
    mysql->status=MYSQL_STATUS_READY;
    mysql->reconnect=0;
    simple_command(mysql,COM_QUIT,(uchar*) 0,0,1);
    end_server(mysql);
  }
}
