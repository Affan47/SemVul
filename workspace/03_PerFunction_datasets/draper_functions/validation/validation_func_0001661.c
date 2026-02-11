listen (int num)
{
  if (::listen (rep->sock, num) == -1)
    throw sockerr (errno, "sockbuf::listen", sockname.text.c_str());
}
