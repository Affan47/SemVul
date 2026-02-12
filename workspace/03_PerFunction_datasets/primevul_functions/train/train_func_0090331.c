static CURLcode add_per_transfer(struct per_transfer **per)
{
  struct per_transfer *p;
  p = calloc(sizeof(struct per_transfer), 1);
  if(!p)
    return CURLE_OUT_OF_MEMORY;
  if(!transfers)

    transfersl = transfers = p;
  else {

    transfersl->next = p;

    p->prev = transfersl;

    transfersl = p;
  }
  *per = p;
  all_xfers++;
  return CURLE_OK;
}
