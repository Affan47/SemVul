static int waitproxyconnect_getsock(struct connectdata *conn,
                                    curl_socket_t *sock,
                                    int numsocks)
{
  if(!numsocks)
    return GETSOCK_BLANK;

  sock[0] = conn->sock[FIRSTSOCKET];


  if(conn->tunnel_state[FIRSTSOCKET] == TUNNEL_CONNECT)
    return GETSOCK_READSOCK(0);

  return GETSOCK_WRITESOCK(0);
}
