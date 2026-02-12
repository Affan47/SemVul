_compare_routerinfo_by_ip_and_bw(const void **a, const void **b)
{
  routerinfo_t *first = *(routerinfo_t **)a, *second = *(routerinfo_t **)b;
  int first_is_auth, second_is_auth;
  uint32_t bw_first, bw_second;


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

  else if (first->is_running && !second->is_running)
    return -1;
  else if (!first->is_running && second->is_running)
    return 1;

  bw_first = router_get_advertised_bandwidth(first);
  bw_second = router_get_advertised_bandwidth(second);

  if (bw_first > bw_second)
     return -1;
  else if (bw_first < bw_second)
    return 1;


  return fast_memcmp(first->cache_info.identity_digest,
                     second->cache_info.identity_digest,
                     DIGEST_LEN);
}
