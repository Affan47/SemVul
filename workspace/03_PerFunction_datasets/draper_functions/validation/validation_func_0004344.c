read (void* buf, int len)
{
  if (rep->rtmo != -1 && is_readready (rep->rtmo)==0) {
    throw sockerr (ETIMEDOUT, "sockbuf::read", sockname.text.c_str());
  }

  if (rep->oob && atmark ())
    throw sockoob ();

  int rval = 0;

  if ((rval = ::recv (rep->sock, (char*) buf, len, 0)) == -1)
    throw sockerr (errno, "sockbuf::read", sockname.text.c_str());
  return rval;
}
