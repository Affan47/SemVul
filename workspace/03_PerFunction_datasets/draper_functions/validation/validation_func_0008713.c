__nss_cdb_dogetent(struct nss_cdb *dbp,
                   void *result, char *buf, size_t bufl, int *errnop) {
  int r;
  unsigned lastpos;

  if (!isopen(dbp) && !__nss_cdb_dosetent(dbp))
    return *errnop = errno, NSS_STATUS_UNAVAIL;

  while((lastpos = dbp->lastpos, r = cdb_seqnext(&dbp->lastpos, &dbp->cdb)) > 0)
  {
    if (cdb_keylen(&dbp->cdb) < 2) continue;
    if (((const char *)cdb_getkey(&dbp->cdb))[0] == ':')
      continue;
    if (cdb_datalen(&dbp->cdb) >= bufl)
      return dbp->lastpos = lastpos, *errnop = ERANGE, NSS_STATUS_TRYAGAIN;
    cdb_readdata(&dbp->cdb, buf);
    buf[cdb_datalen(&dbp->cdb)] = '\0';
    if ((r = dbp->parsefn(result, buf, bufl)) == 0)
      return dbp->lastpos = lastpos, *errnop = ERANGE, NSS_STATUS_TRYAGAIN;
    if (r > 0)
      return NSS_STATUS_SUCCESS;
  }
  if (r < 0)
    return *errnop = errno, NSS_STATUS_UNAVAIL;
  else
    return *errnop = ENOENT, NSS_STATUS_NOTFOUND;
}
