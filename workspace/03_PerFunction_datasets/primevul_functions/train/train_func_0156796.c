compare_routerinfo_by_ip_and_bw_(const void **a, const void **b)
{
  routerinfo_t *first = *(routerinfo_t **)a, *second = *(routerinfo_t **)b;
  int first_is_auth, second_is_auth;
  uint32_t bw_kb_first, bw_kb_second;
  const node_t *node_first, *node_second;
  int first_is_running, second_is_running;


  if (first->addr < second->addr)
    return -1;
  else if (first->addr > second->addr)
    return 1;


  first_is_auth =
    router_digest_is_trusted_dir(first->cache_info.identity_digest);
  second_is_auth =
    router_digest_is_trusted_dir(second->cache_info.identity_digest);

  if (first_is_auth && !second_is_auth)
    return -1;
  else if (!first_is_auth && second_is_auth)
    return 1;

  node_first = node_get_by_id(first->cache_info.identity_digest);
  node_second = node_get_by_id(second->cache_info.identity_digest);
  first_is_running = node_first && node_first->is_running;
  second_is_running = node_second && node_second->is_running;

  if (first_is_running && !second_is_running)
    return -1;
  else if (!first_is_running && second_is_running)
    return 1;

  bw_kb_first = dirserv_get_bandwidth_for_router_kb(first);
  bw_kb_second = dirserv_get_bandwidth_for_router_kb(second);

  if (bw_kb_first > bw_kb_second)
     return -1;
  else if (bw_kb_first < bw_kb_second)
    return 1;


  return fast_memcmp(first->cache_info.identity_digest,
                     second->cache_info.identity_digest,
                     DIGEST_LEN);
}
