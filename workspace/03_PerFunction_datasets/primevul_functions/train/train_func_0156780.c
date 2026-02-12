dirserv_get_credible_bandwidth_kb(const routerinfo_t *ri)
{
  int threshold;
  uint32_t bw_kb = 0;
  long mbw_kb;

  tor_assert(ri);

  if (!(dirserv_query_measured_bw_cache_kb(ri->cache_info.identity_digest,
                                       &mbw_kb, NULL))) {
    threshold = get_options()->MinMeasuredBWsForAuthToIgnoreAdvertised;
    if (routers_with_measured_bw > threshold) {

      bw_kb = 0;
    } else {

      bw_kb = router_get_advertised_bandwidth_capped(ri) / 1000;
    }
  } else {

    bw_kb = (uint32_t)mbw_kb;
  }

  return bw_kb;
}
