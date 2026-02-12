static int client_mpvio_read_packet(struct st_plugin_vio *mpv, uchar **buf)
{
  MCPVIO_EXT *mpvio= (MCPVIO_EXT*)mpv;
  MYSQL *mysql= mpvio->mysql;
  ulong  pkt_len;


  if (mpvio->cached_server_reply.pkt)
  {
    *buf= mpvio->cached_server_reply.pkt;
    mpvio->cached_server_reply.pkt= 0;
    mpvio->packets_read++;
    return mpvio->cached_server_reply.pkt_len;
  }

  if (mpvio->packets_read == 0)
  {


    if (client_mpvio_write_packet(mpv, 0, 0))
      return (int)packet_error;
  }


  pkt_len= (*mysql->methods->read_change_user_result)(mysql);
  mpvio->last_read_packet_len= pkt_len;
  *buf= mysql->net.read_pos;


  if (pkt_len == packet_error || **buf == 254)
    return (int)packet_error;


  if (pkt_len && **buf == 1)
  {
    (*buf)++;
    pkt_len--;
  }
  mpvio->packets_read++;
  return pkt_len;
}
