update_total_bandwidth_weights(const routerstatus_t *rs,
                               int is_exit, int is_guard,
                               int64_t *G, int64_t *M, int64_t *E, int64_t *D,
                               int64_t *T)
{
  int default_bandwidth = rs->bandwidth_kb;
  int guardfraction_bandwidth = 0;

  if (!rs->has_bandwidth) {
    log_info(LD_BUG, "Missing consensus bandwidth for router %s",
             rs->nickname);
    return;
  }


  if (rs->has_guardfraction) {
    guardfraction_bandwidth_t guardfraction_bw;

    tor_assert(is_guard);

    guard_get_guardfraction_bandwidth(&guardfraction_bw,
                                      rs->bandwidth_kb,
                                      rs->guardfraction_percentage);

    default_bandwidth = guardfraction_bw.guard_bw;
    guardfraction_bandwidth = guardfraction_bw.non_guard_bw;
  }


  *T += default_bandwidth;
  if (is_exit && is_guard) {

    *D += default_bandwidth;
    if (rs->has_guardfraction) {
      *E += guardfraction_bandwidth;
    }

  } else if (is_exit) {

    *E += default_bandwidth;

  } else if (is_guard) {

    *G += default_bandwidth;
    if (rs->has_guardfraction) {
      *M += guardfraction_bandwidth;
    }

  } else {

    *M += default_bandwidth;
  }
}
