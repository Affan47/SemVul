_nss_nis_gethostbyaddr_r (const void *addr, socklen_t addrlen, int af,
			  struct hostent *host, char *buffer, size_t buflen,
			  int *errnop, int *h_errnop)
{
  char *domain;
  if (__builtin_expect (yp_get_default_domain (&domain), 0))
    return NSS_STATUS_UNAVAIL;

  uintptr_t pad = -(uintptr_t) buffer % __alignof__ (struct parser_data);
  buffer += pad;

  struct parser_data *data = (void *) buffer;
  if (__builtin_expect (buflen < sizeof *data + 1 + pad, 0))
    {
      *errnop = ERANGE;
      *h_errnop = NETDB_INTERNAL;
      return NSS_STATUS_TRYAGAIN;
    }
  buflen -= pad;

  char *buf = inet_ntoa (*(const struct in_addr *) addr);

  char *result;
  int len;
  int yperr = yp_match (domain, "hosts.byaddr", buf, strlen (buf), &result,
			&len);

  if (__builtin_expect (yperr != YPERR_SUCCESS, 0))
    {
      enum nss_status retval = yperr2nss (yperr);

      if (retval == NSS_STATUS_TRYAGAIN)
	{
	  *h_errnop = TRY_AGAIN;
	  *errnop = errno;
	}
      else if (retval == NSS_STATUS_NOTFOUND)
	*h_errnop = HOST_NOT_FOUND;

      return retval;
    }

  const size_t linebuflen = buffer + buflen - data->linebuffer;
  if (__builtin_expect ((size_t) (len + 1) > linebuflen, 0))
    {
      free (result);
      *errnop = ERANGE;
      *h_errnop = NETDB_INTERNAL;
      return NSS_STATUS_TRYAGAIN;
    }

  char *p = strncpy (data->linebuffer, result, len);
  data->linebuffer[len] = '\0';
  while (isspace (*p))
    ++p;
  free (result);

  int parse_res = parse_line (p, host, data, buflen, errnop, af,
			      ((_res.options & RES_USE_INET6)
			       ? AI_V4MAPPED : 0));
  if (__builtin_expect (parse_res < 1, 0))
    {
      if (parse_res == -1)
	{
	  *h_errnop = NETDB_INTERNAL;
	  return NSS_STATUS_TRYAGAIN;
	}
      else
	{
	  *h_errnop = HOST_NOT_FOUND;
	  return NSS_STATUS_NOTFOUND;
	}
    }

  *h_errnop = NETDB_SUCCESS;
  return NSS_STATUS_SUCCESS;
}
