router_is_active(const routerinfo_t *ri, const node_t *node, time_t now)
{
  time_t cutoff = now - ROUTER_MAX_AGE_TO_PUBLISH;
  if (ri->cache_info.published_on < cutoff) {
    return 0;
  }
  if (!node->is_running || !node->is_valid || ri->is_hibernating) {
    return 0;
  }


  if (!ri->bandwidthcapacity) {
    if (get_options()->TestingTorNetwork) {
      if (get_options()->TestingMinExitFlagThreshold > 0) {


        return 0;
      }
    } else {

      return 0;
    }
  }
  return 1;
}
