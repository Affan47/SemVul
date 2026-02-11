sanei_bjnp_open (SANE_String_Const devname, SANE_Int * dn)
{
  int result;
  char hostname[256];
  char pid_str[64];


  PDBG (bjnp_dbg (LOG_INFO, "sanei_bjnp_open(%s, %d):\n", devname, *dn));

  result = bjnp_allocate_device (devname, dn, NULL);
  if ( (result != BJNP_STATUS_GOOD) && (result != BJNP_STATUS_ALREADY_ALLOCATED ) )
    return SANE_STATUS_INVAL;


  gethostname (hostname, 256);
  hostname[255] = '\0';
  sprintf (pid_str, "Process ID = %d", getpid ());

  bjnp_send_job_details (*dn, hostname, getusername (), pid_str);

  if (bjnp_open_tcp (*dn) != 0)
    {
      return SANE_STATUS_INVAL;
    }

  return SANE_STATUS_GOOD;
}
