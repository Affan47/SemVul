string_log_address(gstring * g,
  address_item *addr, BOOL all_parents, BOOL success)
{
BOOL add_topaddr = TRUE;
address_item *topaddr;


for (topaddr = addr; topaddr->parent; topaddr = topaddr->parent) ;


if (  testflag(addr, af_pfr)
   || (  success
      && addr->router && addr->router->log_as_local
      && addr->transport && addr->transport->info->local
   )  )
  {
  if (testflag(addr, af_file) && addr->local_part[0] != '/')
    g = string_catn(g, CUS"save ", 5);
  g = string_get_localpart(addr, g);
  }


else
  {
  uschar * cmp = g->s + g->ptr;

  if (addr->local_part)
    {
    const uschar * s;
    g = string_get_localpart(addr, g);
    g = string_catn(g, US"@", 1);
    s = addr->domain;
#ifdef SUPPORT_I18N
    if (testflag(addr, af_utf8_downcvt))
      s = string_localpart_utf8_to_alabel(s, NULL);
#endif
    g = string_cat(g, s);
    }
  else
    g = string_cat(g, addr->address);


  string_from_gstring(g);
  if (  strcmpic(cmp, topaddr->address) == 0
     && Ustrncmp(cmp, topaddr->address, Ustrchr(cmp, '@') - cmp) == 0
     && !addr->onetime_parent
     && (!all_parents || !addr->parent || addr->parent == topaddr)
     )
    add_topaddr = FALSE;
  }


if (  (all_parents || testflag(addr, af_pfr))
   && addr->parent
   && addr->parent != topaddr)
  {
  uschar *s = US" (";
  address_item *addr2;
  for (addr2 = addr->parent; addr2 != topaddr; addr2 = addr2->parent)
    {
    g = string_catn(g, s, 2);
    g = string_cat (g, addr2->address);
    if (!all_parents) break;
    s = US", ";
    }
  g = string_catn(g, US")", 1);
  }


if (add_topaddr)
  g = string_append(g, 3,
    US" <",
    addr->onetime_parent ? addr->onetime_parent : topaddr->address,
    US">");

return g;
}
