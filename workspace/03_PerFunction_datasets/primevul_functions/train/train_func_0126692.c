child_done(address_item *addr, uschar *now)
{
address_item *aa;
while (addr->parent)
  {
  addr = addr->parent;
  if (--addr->child_count > 0) return;
  address_done(addr, now);


  for (aa = addr->parent; aa; aa = aa->parent)
    if (Ustrcmp(aa->address, addr->address) == 0) break;
  if (aa) continue;

  deliver_msglog("%s %s: children all complete\n", now, addr->address);
  DEBUG(D_deliver) debug_printf("%s: children all complete\n", addr->address);
  }
}
