string_log_address(address_item *addr, BOOL all_parents, BOOL success)
{
int size = 64;
int ptr = 0;
BOOL add_topaddr = TRUE;
uschar *yield = store_get(size);
address_item *topaddr;


for (topaddr = addr; topaddr->parent != NULL; topaddr = topaddr->parent);


if (testflag(addr, af_pfr) ||
      (success &&
       addr->router != NULL && addr->router->log_as_local &&
       addr->transport != NULL && addr->transport->info->local))
  {
  if (testflag(addr, af_file) && addr->local_part[0] != '/')
    yield = string_cat(yield, &size, &ptr, CUS"save ", 5);
  yield = string_get_localpart(addr, yield, &size, &ptr);
  }


else
  {
  if (addr->local_part != NULL)
    {
    yield = string_get_localpart(addr, yield, &size, &ptr);
    yield = string_cat(yield, &size, &ptr, US"@", 1);
    yield = string_cat(yield, &size, &ptr, addr->domain,
      Ustrlen(addr->domain) );
    }
  else
    {
    yield = string_cat(yield, &size, &ptr, addr->address, Ustrlen(addr->address));
    }
  yield[ptr] = 0;


  if (strcmpic(yield, topaddr->address) == 0 &&
      Ustrncmp(yield, topaddr->address, Ustrchr(yield, '@') - yield) == 0 &&
      addr->onetime_parent == NULL &&
      (!all_parents || addr->parent == NULL || addr->parent == topaddr))
    add_topaddr = FALSE;
  }


if ((all_parents || testflag(addr, af_pfr)) &&
    addr->parent != NULL &&
    addr->parent != topaddr)
  {
  uschar *s = US" (";
  address_item *addr2;
  for (addr2 = addr->parent; addr2 != topaddr; addr2 = addr2->parent)
    {
    yield = string_cat(yield, &size, &ptr, s, 2);
    yield = string_cat(yield, &size, &ptr, addr2->address, Ustrlen(addr2->address));
    if (!all_parents) break;
    s = US", ";
    }
  yield = string_cat(yield, &size, &ptr, US")", 1);
  }


if (add_topaddr)
  {
  yield = string_cat(yield, &size, &ptr, US" <", 2);

  if (addr->onetime_parent == NULL)
    yield = string_cat(yield, &size, &ptr, topaddr->address,
      Ustrlen(topaddr->address));
  else
    yield = string_cat(yield, &size, &ptr, addr->onetime_parent,
      Ustrlen(addr->onetime_parent));

  yield = string_cat(yield, &size, &ptr, US">", 1);
  }

yield[ptr] = 0;
return yield;
}
