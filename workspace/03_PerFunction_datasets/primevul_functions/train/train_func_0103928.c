ospf_write_frags (int fd, struct ospf_packet *op, struct ip *iph,
                  struct msghdr *msg, unsigned int maxdatasize,
                  unsigned int mtu, int flags, u_char type)
{
#define OSPF_WRITE_FRAG_SHIFT 3
  u_int16_t offset;
  struct iovec *iovp;
  int ret;

  assert ( op->length == stream_get_endp(op->s) );
  assert (msg->msg_iovlen == 2);


  iph->ip_off |= IP_MF;


  offset = maxdatasize >> OSPF_WRITE_FRAG_SHIFT;

  iovp = &msg->msg_iov[1];

  while ( (stream_get_endp(op->s) - stream_get_getp (op->s))
         > maxdatasize )
    {

      iovp->iov_len = offset << OSPF_WRITE_FRAG_SHIFT;
      iph->ip_len = iovp->iov_len + sizeof (struct ip);
      assert (iph->ip_len <= mtu);

      sockopt_iphdrincl_swab_htosys (iph);

      ret = sendmsg (fd, msg, flags);

      sockopt_iphdrincl_swab_systoh (iph);

      if (ret < 0)
        zlog_warn ("*** ospf_write_frags: sendmsg failed to %s,"
		   " id %d, off %d, len %d, mtu %u failed with %s",
		   inet_ntoa (iph->ip_dst),
		   iph->ip_id,
		   iph->ip_off,
		   iph->ip_len,
		   mtu,
		   safe_strerror (errno));

      if (IS_DEBUG_OSPF_PACKET (type - 1, SEND))
        {
          zlog_debug ("ospf_write_frags: sent id %d, off %d, len %d to %s\n",
                     iph->ip_id, iph->ip_off, iph->ip_len,
                     inet_ntoa (iph->ip_dst));
          if (IS_DEBUG_OSPF_PACKET (type - 1, DETAIL))
            {
              zlog_debug ("-----------------IP Header Dump----------------------");
              ospf_ip_header_dump (iph);
              zlog_debug ("-----------------------------------------------------");
            }
        }

      iph->ip_off += offset;
      stream_forward_getp (op->s, iovp->iov_len);
      iovp->iov_base = STREAM_PNT (op->s);
    }


  iovp->iov_len = stream_get_endp(op->s) - stream_get_getp (op->s);
  iph->ip_len = iovp->iov_len + sizeof (struct ip);
  iph->ip_off &= (~IP_MF);
}
