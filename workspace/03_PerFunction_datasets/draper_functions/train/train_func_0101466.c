netio_mcast_set_ttl(netio_desc_t *nio,int ttl)
{
   if (nio->type == NETIO_TYPE_MCAST)
      return(-1);

   return(udp_mcast_set_ttl(netio_get_fd(nio),ttl));
}
