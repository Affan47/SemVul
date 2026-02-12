sort_remote_deliveries(void)
{
int sep = 0;
address_item **aptr = &addr_remote;
const uschar *listptr = remote_sort_domains;
uschar *pattern;
uschar patbuf[256];

while (  *aptr
      && (pattern = string_nextinlist(&listptr, &sep, patbuf, sizeof(patbuf)))
      )
  {
  address_item *moved = NULL;
  address_item **bptr = &moved;

  while (*aptr)
    {
    address_item **next;
    deliver_domain = (*aptr)->domain;
    if (match_isinlist(deliver_domain, (const uschar **)&pattern, UCHAR_MAX+1,
          &domainlist_anchor, NULL, MCL_DOMAIN, TRUE, NULL) == OK)
      {
      aptr = &(*aptr)->next;
      continue;
      }

    next = &(*aptr)->next;
    while (  *next
	  && (deliver_domain = (*next)->domain,
            match_isinlist(deliver_domain, (const uschar **)&pattern, UCHAR_MAX+1,
              &domainlist_anchor, NULL, MCL_DOMAIN, TRUE, NULL)) != OK
	  )
      next = &(*next)->next;


    if (!*next)
      {
      *next = moved;
      break;
      }

    *bptr = *aptr;
    *aptr = *next;
    *next = NULL;
    bptr = next;
    aptr = &(*aptr)->next;
    }


  if (!*aptr) *aptr = moved;
  }

DEBUG(D_deliver)
  {
  address_item *addr;
  debug_printf("remote addresses after sorting:\n");
  for (addr = addr_remote; addr; addr = addr->next)
    debug_printf("  %s\n", addr->address);
  }
}
