address_done(address_item *addr, uschar *now)
{
address_item *dup;

update_spool = TRUE;


if (!addr->parent)
  {
  tree_add_nonrecipient(addr->unique);
  tree_add_nonrecipient(addr->address);
  }


else if (testflag(addr, af_homonym))
  {
  if (addr->transport)
    tree_add_nonrecipient(
      string_sprintf("%s/%s", addr->unique + 3, addr->transport->name));
  }


else tree_add_nonrecipient(addr->unique);


for (dup = addr_duplicate; dup; dup = dup->next)
  if (Ustrcmp(addr->unique, dup->unique) == 0)
    {
    tree_add_nonrecipient(dup->unique);
    child_done(dup, now);
    }
}
