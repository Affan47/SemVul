bgp_write_notify (struct peer *peer)
{
  int ret;
  u_char type;
  struct stream *s;


  s = stream_fifo_head (peer->obuf);
  if (!s)
    return 0;
  assert (stream_get_endp (s) >= BGP_HEADER_SIZE);


  ret = writen (peer->fd, STREAM_DATA (s), stream_get_endp (s));
  if (ret <= 0)
    {
      BGP_EVENT_ADD (peer, TCP_fatal_error);
      return 0;
    }


  stream_set_getp (s, BGP_MARKER_SIZE + 2);
  type = stream_getc (s);

  assert (type == BGP_MSG_NOTIFY);


  peer->notify_out++;


  peer->v_start *= 2;


  if (peer->v_start >= (60 * 2))
    peer->v_start = (60 * 2);

  BGP_EVENT_ADD (peer, BGP_Stop);

  return 0;
}
