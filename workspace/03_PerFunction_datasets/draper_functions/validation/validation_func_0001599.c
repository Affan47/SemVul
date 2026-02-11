crule_directcon(int numargs, void *crulearg[])
{
#if !defined(CR_DEBUG) && !defined(CR_CHKCONF)
  int i;
  struct Client *acptr;


  for (i = 0; i <= HighestFd; i++)
  {
    if (!(acptr = LocalClientArray[i]) || !IsServer(acptr))
      continue;
    if (match((char *)crulearg[0], cli_name(acptr)))
      continue;
    return (1);
  }
#endif
  return (0);
}
