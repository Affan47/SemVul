dirserv_get_bandwidth_for_router_kb(const routerinfo_t *ri)
{
  uint32_t bw_kb = 0;


  long mbw_kb = 0;

  if (ri) {


    if (dirserv_query_measured_bw_cache_kb(ri->cache_info.identity_digest,
                                        &mbw_kb, NULL)) {

      bw_kb = (uint32_t)mbw_kb;
    } else {

      bw_kb = router_get_advertised_bandwidth(ri) / 1000;
    }
  }

  return bw_kb;
}
