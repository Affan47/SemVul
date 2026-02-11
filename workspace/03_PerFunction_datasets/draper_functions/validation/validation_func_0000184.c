getNextRandGid (LDAP * ld, gid_t min_gid, gid_t max_gid)
{
  LDAPMessage	  *res;
  gid_t		  next_gid = 0;
  int		  i = 0, id_pass = 0, ldapres = 0, filtsize = 40;
  struct timeval  timeout;
  char		  *filter = NULL;
  char *attrs[2] = {
    "gidNumber",
    NULL
  };

  timeout = globalLdap->timeout;

  filter = (char *) malloc (sizeof (char) * filtsize);
  if (filter == NULL)
    return -1;

  id_pass = cfg_get_int ("LDAP", "ID_MAX_PASSES");
  if (id_pass < 1)
    id_pass = 1000;

  while (i < id_pass)
  {
    next_gid = cRandom (min_gid, max_gid);
    bzero (filter, filtsize);
    snprintf (filter, filtsize, "(gidNumber=%d)", (int)next_gid);
    if (ldap_search_st (ld, globalLdap->group_base, LDAP_SCOPE_SUBTREE,
	  filter, attrs, 0, &timeout,
	  &res) != LDAP_SUCCESS)
    {
      Free (filter);
      CPU_ldapPerror (ld, globalLdap, "getNextRandGid: ldap_search_st");
      return -1;
    }
    ldapres = ldap_count_entries (ld, res);
    if (ldapres == 0)
      break;
    ++i;
  }
  Free (filter);
  if (i == id_pass)
  {
    fprintf (stderr, "ldap: getNextRandGid: Unable to find new gid.\n");
    return -1;
  }
  return next_gid;
}
