int ma_multi_command(MYSQL *mysql, enum enum_multi_status status)
{
  NET *net= &mysql->net;

  switch (status) {
  case COM_MULTI_OFF:
    ma_net_clear(net);
    net->extension->multi_status= status;
    return 0;
  case COM_MULTI_ENABLED:
    if (net->extension->multi_status > COM_MULTI_DISABLED)
      return 1;
    ma_net_clear(net);
    net->extension->multi_status= status;
    return 0;
  case COM_MULTI_DISABLED:


    net->extension->multi_status= status;
    return 0;
  case COM_MULTI_END:
  {
    size_t len= net->write_pos - net->buff - NET_HEADER_SIZE;

    if (len < NET_HEADER_SIZE)
    {
      ma_net_clear(net);
      return 1;
    }
    net->extension->multi_status= COM_MULTI_OFF;
    return ma_net_flush(net);
  }
  case COM_MULTI_CANCEL:
    ma_net_clear(net);
    net->extension->multi_status= COM_MULTI_OFF;
    return 0;
  default:
    return 1;
  }
}
