accept (ACE_SSL_SOCK_Stream &new_stream,
                               ACE_Addr *remote_addr,
                               ACE_Time_Value *timeout,
                               bool restart,
                               bool reset_new_handle) const
{
  ACE_TRACE ("ACE_SSL_SOCK_Acceptor::accept");


  ACE_Countdown_Time countdown (timeout);

  ACE_SOCK_Stream temp_stream;
  if (-1 == this->acceptor_.accept (temp_stream,
                                    remote_addr,
                                    timeout,
                                    restart,
                                    reset_new_handle))
    return -1;

  (void) countdown.update ();

  new_stream.set_handle (temp_stream.get_handle ());
  temp_stream.set_handle (ACE_INVALID_HANDLE);

  if (this->ssl_accept (new_stream, timeout) == -1)
    {
      new_stream.close ();
      new_stream.set_handle (ACE_INVALID_HANDLE);
      return -1;
    }

  return 0;

}
