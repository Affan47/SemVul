adrbk_listdel_all(AdrBk *ab, a_c_arg_t entry_num)
{
    char **p;
    AdrBk_Entry *ae;

    dprint((3, "- adrbk_listdel_all(%ld) -\n", (long) entry_num));

    if(!ab || entry_num >= ab->count)
      return -2;

    ae = adrbk_get_ae(ab, entry_num);

    if(ae->tag != List)
      return -1;


    for(p = ae->addr.list; p && *p; p++)
      if(*p != empty)
        fs_give((void **)p);

    if(ae->addr.list)
      fs_give((void **) &ae->addr.list);

    ae->addr.list = NULL;

    return 0;
}
