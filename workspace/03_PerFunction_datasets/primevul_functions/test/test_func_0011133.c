dirserv_compute_performance_thresholds(routerlist_t *rl)
{
  int n_active, n_active_nonexit, n_familiar;
  uint32_t *uptimes, *bandwidths, *bandwidths_excluding_exits;
  long *tks;
  double *mtbfs, *wfus;
  time_t now = time(NULL);


  stable_uptime = 0;
  stable_mtbf = 0;
  fast_bandwidth = 0;
  guard_bandwidth_including_exits = 0;
  guard_bandwidth_excluding_exits = 0;
  guard_tk = 0;
  guard_wfu = 0;
  total_bandwidth = 0;
  total_exit_bandwidth = 0;


  n_active = n_active_nonexit = 0;

  uptimes = tor_malloc(sizeof(uint32_t)*smartlist_len(rl->routers));

  bandwidths = tor_malloc(sizeof(uint32_t)*smartlist_len(rl->routers));

  bandwidths_excluding_exits =
    tor_malloc(sizeof(uint32_t)*smartlist_len(rl->routers));

  mtbfs = tor_malloc(sizeof(double)*smartlist_len(rl->routers));

  tks = tor_malloc(sizeof(long)*smartlist_len(rl->routers));

  wfus = tor_malloc(sizeof(double)*smartlist_len(rl->routers));


  SMARTLIST_FOREACH(rl->routers, routerinfo_t *, ri, {
    if (router_is_active(ri, now)) {
      const char *id = ri->cache_info.identity_digest;
      uint32_t bw;
      ri->is_exit = (!router_exit_policy_rejects_all(ri) &&
                    exit_policy_is_general_exit(ri->exit_policy));
      uptimes[n_active] = (uint32_t)real_uptime(ri, now);
      mtbfs[n_active] = rep_hist_get_stability(id, now);
      tks  [n_active] = rep_hist_get_weighted_time_known(id, now);
      bandwidths[n_active] = bw = router_get_advertised_bandwidth(ri);
      total_bandwidth += bw;
      if (ri->is_exit && !ri->is_bad_exit) {
        total_exit_bandwidth += bw;
      } else {
        bandwidths_excluding_exits[n_active_nonexit] = bw;
        ++n_active_nonexit;
      }
      ++n_active;
    }
  });


  if (n_active) {

    stable_uptime = median_uint32(uptimes, n_active);

    stable_mtbf = median_double(mtbfs, n_active);

    fast_bandwidth = find_nth_uint32(bandwidths, n_active, n_active/8);

    if (fast_bandwidth < ROUTER_REQUIRED_MIN_BANDWIDTH/2)
      fast_bandwidth = bandwidths[n_active/4];
    guard_bandwidth_including_exits = bandwidths[(n_active-1)/2];
    guard_tk = find_nth_long(tks, n_active, n_active/8);
  }

  if (guard_tk > TIME_KNOWN_TO_GUARANTEE_FAMILIAR)
    guard_tk = TIME_KNOWN_TO_GUARANTEE_FAMILIAR;

  if (fast_bandwidth > BANDWIDTH_TO_GUARANTEE_FAST)
    fast_bandwidth = BANDWIDTH_TO_GUARANTEE_FAST;


  n_familiar = 0;
  SMARTLIST_FOREACH(rl->routers, routerinfo_t *, ri, {
      if (router_is_active(ri, now)) {
        const char *id = ri->cache_info.identity_digest;
        long tk = rep_hist_get_weighted_time_known(id, now);
        if (tk < guard_tk)
          continue;
        wfus[n_familiar++] = rep_hist_get_weighted_fractional_uptime(id, now);
      }
    });
  if (n_familiar)
    guard_wfu = median_double(wfus, n_familiar);
  if (guard_wfu > WFU_TO_GUARANTEE_GUARD)
    guard_wfu = WFU_TO_GUARANTEE_GUARD;

  enough_mtbf_info = rep_hist_have_measured_enough_stability();

  if (n_active_nonexit) {
    guard_bandwidth_excluding_exits =
      median_uint32(bandwidths_excluding_exits, n_active_nonexit);
  }

  log(LOG_INFO, LD_DIRSERV,
      "Cutoffs: For Stable, %lu sec uptime, %lu sec MTBF. "
      "For Fast: %lu bytes/sec. "
      "For Guard: WFU %.03lf%%, time-known %lu sec, "
      "and bandwidth %lu or %lu bytes/sec. We%s have enough stability data.",
      (unsigned long)stable_uptime,
      (unsigned long)stable_mtbf,
      (unsigned long)fast_bandwidth,
      guard_wfu*100,
      (unsigned long)guard_tk,
      (unsigned long)guard_bandwidth_including_exits,
      (unsigned long)guard_bandwidth_excluding_exits,
      enough_mtbf_info ? "" : " don't ");

  tor_free(uptimes);
  tor_free(mtbfs);
  tor_free(bandwidths);
  tor_free(bandwidths_excluding_exits);
  tor_free(tks);
  tor_free(wfus);
}
