dirserv_set_router_is_running(routerinfo_t *router, time_t now)
{


  int answer;

  if (router_is_me(router)) {

    answer = ! we_are_hibernating();
  } else if (router->is_hibernating &&
             (router->cache_info.published_on +
              HIBERNATION_PUBLICATION_SKEW) > router->last_reachable) {


    answer = 0;
  } else if (get_options()->AssumeReachable) {

    answer = 1;
  } else {


    answer = (now < router->last_reachable + REACHABLE_TIMEOUT);
  }

  if (!answer && running_long_enough_to_decide_unreachable()) {


    time_t when = now;
    if (router->last_reachable &&
        router->last_reachable + REACHABILITY_TEST_CYCLE_PERIOD < now)
      when = router->last_reachable + REACHABILITY_TEST_CYCLE_PERIOD;
    rep_hist_note_router_unreachable(router->cache_info.identity_digest, when);
  }

  router->is_running = answer;
}
