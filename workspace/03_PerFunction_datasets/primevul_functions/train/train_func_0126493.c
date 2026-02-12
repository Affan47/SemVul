tfo_out_check(int sock)
{
# if defined(TCP_INFO) && defined(EXIM_HAVE_TCPI_UNACKED)
struct tcp_info tinfo;
socklen_t len = sizeof(tinfo);

switch (tcp_out_fastopen)
  {


  case TFO_ATTEMPTED_NODATA:
    if (  getsockopt(sock, IPPROTO_TCP, TCP_INFO, &tinfo, &len) == 0
       && tinfo.tcpi_state == TCP_SYN_SENT
       && tinfo.tcpi_unacked > 1
       )
      {
      DEBUG(D_transport|D_v)
	debug_printf("TCP_FASTOPEN tcpi_unacked %d\n", tinfo.tcpi_unacked);
      tcp_out_fastopen = TFO_USED_NODATA;
      }
    break;


  case TFO_ATTEMPTED_DATA:
    if (  getsockopt(sock, IPPROTO_TCP, TCP_INFO, &tinfo, &len) == 0
       && tinfo.tcpi_state == TCP_ESTABLISHED
       )
      if (tinfo.tcpi_options & TCPI_OPT_SYN_DATA)
	{
	DEBUG(D_transport|D_v) debug_printf("TFO: data was acked\n");
	tcp_out_fastopen = TFO_USED_DATA;
	}
      else
	{
	DEBUG(D_transport|D_v) debug_printf("TFO: had to retransmit\n");
	tcp_out_fastopen = TFO_NOT_USED;
	}
    break;
  }
# endif
}
