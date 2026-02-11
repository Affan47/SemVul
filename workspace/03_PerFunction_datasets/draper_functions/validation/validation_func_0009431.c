remove_handler (ACE_HANDLE handle,
                                      ACE_Reactor_Mask mask)
{
  ACE_TRACE ("ACE_Dev_Poll_Reactor::remove_handler");

  ACE_MT (ACE_GUARD_RETURN (ACE_Dev_Poll_Reactor_Token, mon, this->token_, -1));

  return this->remove_handler_i (handle, mask);
}
