router_reload_router_list(void)
{
  routerlist_t *rl = router_get_routerlist();
  if (router_reload_router_list_impl(&rl->desc_store))
    return -1;
  if (router_reload_router_list_impl(&rl->extrainfo_store))
    return -1;
  return 0;
}
