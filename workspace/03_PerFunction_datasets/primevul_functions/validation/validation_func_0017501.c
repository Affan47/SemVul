static my_socket mariadb_get_socket(MYSQL *mysql)
{
  my_socket sock= INVALID_SOCKET;
  if (mysql->net.pvio)
  {
    ma_pvio_get_handle(mysql->net.pvio, &sock);

  }


  else if (mysql->options.extension && mysql->options.extension->async_context &&
           mysql->options.extension->async_context->pvio)
  {
    ma_pvio_get_handle(mysql->options.extension->async_context->pvio, &sock);
  }
  return sock;
}
