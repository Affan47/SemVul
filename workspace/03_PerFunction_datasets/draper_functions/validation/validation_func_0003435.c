open (const ACE_INET_Addr &mcast_addr,
                            const ACE_TCHAR *net_if,
                            int reuse_addr)
{
  ACE_TRACE ("ACE_SOCK_Dgram_Mcast::open");


  if (this->get_handle () != ACE_INVALID_HANDLE)
    return 0;


  if (ACE_SOCK::open (SOCK_DGRAM,
                      mcast_addr.get_type (),
                      0,
                      reuse_addr) == -1)
    return -1;

  return this->open_i (mcast_addr, net_if, reuse_addr);
}
