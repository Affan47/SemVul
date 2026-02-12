_dbus_get_is_errno_eagain_or_ewouldblock (int e)
{


#if EAGAIN == EWOULDBLOCK
  return e == EAGAIN;
#else
  return e == EAGAIN || e == EWOULDBLOCK;
#endif
}
