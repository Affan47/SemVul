fix_unset_addr_list(UnsetAddrList* uslist, regex_t* reg)
{
  int i, offset;
  BagNode* en;
  AbsAddrType addr;
  AbsAddrType* paddr;

  for (i = 0; i < uslist->num; i++) {
    if (! NODE_IS_FIXED_ADDR(uslist->us[i].target)) {
      if (NODE_IS_CALLED(uslist->us[i].target))
        return ONIGERR_PARSER_BUG;
      else {


        continue;
      }
    }

    en = BAG_(uslist->us[i].target);
    addr   = en->m.called_addr;
    offset = uslist->us[i].offset;

    paddr = (AbsAddrType* )((char* )reg->ops + offset);
    *paddr = addr;
  }
  return 0;
}
