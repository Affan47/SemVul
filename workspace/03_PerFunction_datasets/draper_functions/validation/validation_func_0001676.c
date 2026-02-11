open (const ACE_Addr &remote, const ACE_Addr &local,
                        int protocol_family, int protocol,
                        int reuse_addr)
{
  ACE_TRACE ("ACE_SOCK_CODgram::open");


  if (remote != ACE_Addr::sap_any)
    {
      if (local == ACE_Addr::sap_any)
        protocol_family = remote.get_type ();
      else
        {
          if (local.get_type () != remote.get_type ())
            {
              errno = EAFNOSUPPORT;
              return -1;
            }
          protocol_family = remote.get_type ();
        }
    }
  else
    {
      if (local != ACE_Addr::sap_any)
        {
          protocol_family = local.get_type ();
        }
    }
  if (ACE_SOCK::open (SOCK_DGRAM,
                      protocol_family,
                      protocol,
                      reuse_addr) == -1)
    {
      return -1;
    }
  else
    {
      bool error = false;

      if (local == ACE_Addr::sap_any && remote == ACE_Addr::sap_any)
        {

          if ((protocol_family == PF_INET
#if defined (ACE_HAS_IPV6)
               || protocol_family == PF_INET6
#endif
              ) && ACE::bind_port (this->get_handle ()) == -1)
            error = true;
        }

      else if (local != ACE_Addr::sap_any && remote == ACE_Addr::sap_any)
        {
          if (ACE_OS::bind (this->get_handle (),
                            (sockaddr *) local.get_addr (),
                            local.get_size ()) == -1)
            error = true;
        }

      else if (local == ACE_Addr::sap_any && remote != ACE_Addr::sap_any)
        {
          if (ACE_OS::connect (this->get_handle (),
                               (sockaddr *) remote.get_addr (),
                               remote.get_size ()) == -1)
            error = true;
        }


      else
        {
          if (ACE_OS::bind (this->get_handle (),
                            (sockaddr *) local.get_addr (),
                            local.get_size ()) == -1
              || ACE_OS::connect (this->get_handle (),
                                  (sockaddr *) remote.get_addr (),
                                  remote.get_size ()) == -1)
            error = true;
        }
      if (error)
        {
          this->close ();
          this->set_handle (ACE_INVALID_HANDLE);
        }
      return error ? -1 : 0;
    }
}
