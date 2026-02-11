ipcache_alloc_item (address_t *ip)
{
  struct ipcache_item *rp;

  g_assert(ip);
  rp = (struct ipcache_item *) malloc (sizeof (struct ipcache_item));
  if (!rp)
    {
      fprintf (stderr, "malloc() failed: %s\n", strerror (errno));
      exit (-1);
    }
  memset (rp, 0, sizeof (struct ipcache_item));

  rp->state = IPCACHE_STATE_PTRREQ;
  address_copy(&rp->ip, ip);
  ipcache_linkresolveip (rp);


  do
    {
      idseed =
	(((idseed + idseed) | (long) time (NULL)) + idseed -
	 0x54bad4a) ^ aseed;
      aseed ^= idseed;
      rp->id = (unsigned short) idseed;
    }
  while (ipcache_findid (rp->id));
  ipcache_linkresolveid (rp);

  return rp;
}
