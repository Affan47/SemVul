end_server(MYSQL *mysql)
{


  if (mysql->net.pvio != 0)
  {
    ma_pvio_close(mysql->net.pvio);
    mysql->net.pvio= 0;
  }
  ma_net_end(&mysql->net);
  free_old_query(mysql);
  return;
}
