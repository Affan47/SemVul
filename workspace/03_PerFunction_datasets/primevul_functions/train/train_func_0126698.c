deliver_split_address(address_item * addr)
{
uschar * address = addr->address;
uschar * domain;
uschar * t;
int len;

if (!(domain = Ustrrchr(address, '@')))
  return DEFER;

len = domain - address;
addr->domain = string_copylc(domain+1);


t = addr->cc_local_part = store_get(len+1);
while(len-- > 0)
  {
  int c = *address++;
  if (c == '\"') continue;
  if (c == '\\')
    {
    *t++ = *address++;
    len--;
    }
  else *t++ = c;
  }
*t = 0;


if (percent_hack_domains)
  {
  int rc;
  uschar *new_address = NULL;
  uschar *local_part = addr->cc_local_part;

  deliver_domain = addr->domain;

  while (  (rc = match_isinlist(deliver_domain, (const uschar **)&percent_hack_domains, 0,
	       &domainlist_anchor, addr->domain_cache, MCL_DOMAIN, TRUE, NULL))
             == OK
	&& (t = Ustrrchr(local_part, '%')) != NULL
	)
    {
    new_address = string_copy(local_part);
    new_address[t - local_part] = '@';
    deliver_domain = string_copylc(t+1);
    local_part = string_copyn(local_part, t - local_part);
    }

  if (rc == DEFER) return DEFER;


  if (new_address)
    {
    address_item *new_parent = store_get(sizeof(address_item));
    *new_parent = *addr;
    addr->parent = new_parent;
    new_parent->child_count = 1;
    addr->address = new_address;
    addr->unique = string_copy(new_address);
    addr->domain = deliver_domain;
    addr->cc_local_part = local_part;
    DEBUG(D_deliver) debug_printf("%%-hack changed address to: %s\n",
      addr->address);
    }
  }


addr->local_part = addr->lc_local_part = string_copylc(addr->cc_local_part);
return OK;
}
