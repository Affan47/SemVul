knocker_core_set_host_ip_string (knocker_core_host_t * hinfo, const char *hostip)
{
  if (hostip == NULL)
    {
      hinfo->ip = NULL;
      return 0;
    }


  if (hinfo->ip == NULL)
    {
      hinfo->ip = malloc (strlen (hostip) + 1);
      strcpy (hinfo->ip, hostip);
    }
  else
    {


      if (strcmp (hinfo->ip, hostip))
        {
          hinfo->ip = realloc (hinfo->ip, strlen (hostip) + 1);
          strcpy (hinfo->ip, hostip);

        }
    }

  return 0;
}
