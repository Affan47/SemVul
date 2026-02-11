internal_nis_setservent (void)
{
  char *domainname;
  struct ypall_callback ypcb;
  enum nss_status status;

  if (yp_get_default_domain (&domainname))
    return NSS_STATUS_UNAVAIL;

  internal_nis_endservent ();

  ypcb.foreach = _nis_saveit;
  ypcb.data = (char *) &intern;
  status = yperr2nss (yp_all (domainname, "services.byname", &ypcb));


  if (intern.next != NULL)
    intern.next->size = intern.offset;

  intern.next = intern.start;
  intern.offset = 0;

  return status;
}
