markMatchexServer(const char *cmask, int minlen)
{
  int cnt = 0;
  int i;
  struct Client *acptr;

  for (i = 0; i < lastNNServer; i++) {
    if ((acptr = server_list[i]))
    {
      if (matchexec(cli_name(acptr), cmask, minlen))
        ClrFlag(acptr, FLAG_MAP);
      else
      {
        SetFlag(acptr, FLAG_MAP);
        cnt++;
      }
    }
  }
  return cnt;
}
