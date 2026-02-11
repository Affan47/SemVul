_nss_nis_getsecretkey (const char *netname, char *skey, char *passwd,
		       int *errnop)
{
  skey[0] = 0;

  if (netname == NULL || passwd == NULL)
    {
      *errnop = EINVAL;
      return NSS_STATUS_UNAVAIL;
    }

  char *domain = strchr (netname, '@');
  if (domain == NULL)
    {
      *errnop = EINVAL;
      return NSS_STATUS_UNAVAIL;
    }
  ++domain;

  char *result;
  int len;
  int yperr = yp_match (domain, "publickey.byname", netname, strlen (netname),
			&result, &len);

  if (__builtin_expect (yperr != YPERR_SUCCESS, 0))
    {
      enum nss_status retval = yperr2nss (yperr);

      if (retval == NSS_STATUS_TRYAGAIN)
	*errnop = errno;
      return retval;
    }

  if (result != NULL)
    {
      char *p = strchr (result, ':');
      if (p != NULL)
	{
	  char buf[2 * (HEXKEYBYTES + 1)];

	  ++p;
	  strncpy (buf, p, 2 * (HEXKEYBYTES + 1));
	  buf[2 * HEXKEYBYTES + 1] = '\0';
	  if (xdecrypt (buf, passwd)
	      && memcmp (buf, &(buf[HEXKEYBYTES]), KEYCHECKSUMSIZE) == 0)
	    {
	      buf[HEXKEYBYTES] = '\0';
	      strcpy (skey, buf);
	    }
	}

      free (result);
    }
  return NSS_STATUS_SUCCESS;
}
