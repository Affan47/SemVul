rinkj_epson_set_common (RinkjEscp *z)
{
  int status = 0;

  if (z->printer_weave >= 0)

    status = rinkj_byte_stream_printf (z->out, "\033(i\001%c%c", 0,
                                       z->printer_weave);

  if (status == 0 && z->unidir >= 0)

    status = rinkj_byte_stream_printf (z->out, "\033U%c", z->unidir);

  if (status == 0 && z->microdot >= 0)

    status = rinkj_byte_stream_printf (z->out, "\033(e\002%c%c%c", 0, 0,
                                       z->microdot);

  return status;
}
