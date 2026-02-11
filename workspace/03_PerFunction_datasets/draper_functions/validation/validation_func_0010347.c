subscribe_i (const ACE_INET_Addr &mcast_addr,
                                   int reuse_addr,
                                   const ACE_TCHAR *net_if)
{
  ACE_TRACE ("ACE_SOCK_Dgram_Mcast::subscribe_i");
  ip_mreq  mreq;
#if defined (ACE_HAS_IPV6)
  ipv6_mreq mreq6;
#endif


  if (this->open (mcast_addr,
                  net_if,
                  reuse_addr) == -1)
    return -1;


  if (net_if == 0)
    {
      int result = this->subscribe_ifs (mcast_addr,
                                        net_if,
                                        reuse_addr);

      if (result != 0)
        return result;
    }

#if defined (ACE_HAS_IPV6)
  if (mcast_addr.get_type () == AF_INET6)
    {
      if (this->make_multicast_ifaddr6 (&mreq6, mcast_addr, net_if) == -1)
        return -1;

      else if (this->ACE_SOCK::set_option (IPPROTO_IPV6,
                                           IPV6_JOIN_GROUP,
                                           &mreq6,
                                           sizeof mreq6) == -1)
        return -1;

      return 0;
    }

#endif


  if (this->make_multicast_ifaddr (&mreq, mcast_addr, net_if) == -1)
    return -1;

  else if (this->ACE_SOCK::set_option (IPPROTO_IP,
                                       IP_ADD_MEMBERSHIP,
                                       &mreq,
                                       sizeof mreq) == -1)
    return -1;

  return 0;
}
