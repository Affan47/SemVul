dirserv_thinks_router_is_hs_dir(const routerinfo_t *router,
                                const node_t *node, time_t now)
{

  long uptime;


  if (stats_n_seconds_working >
      get_options()->MinUptimeHidServDirectoryV2 * 1.1)
    uptime = MIN(rep_hist_get_uptime(router->cache_info.identity_digest, now),
                 real_uptime(router, now));
  else
    uptime = real_uptime(router, now);

  return (router->wants_to_be_hs_dir &&
          router->supports_tunnelled_dir_requests &&
          node->is_stable && node->is_fast &&
          uptime >= get_options()->MinUptimeHidServDirectoryV2 &&
          router_is_active(router, node, now));
}
