static int update_timer(struct Curl_multi *multi)
{
  long timeout_ms;

  if(!multi->timer_cb)
    return 0;
  if(multi_timeout(multi, &timeout_ms)) {
    return -1;
  }
  if(timeout_ms < 0) {
    static const struct timeval none={0, 0};
    if(Curl_splaycomparekeys(none, multi->timer_lastcall)) {
      multi->timer_lastcall = none;


      return multi->timer_cb(multi, -1, multi->timer_userp);
    }
    return 0;
  }


  if(Curl_splaycomparekeys(multi->timetree->key, multi->timer_lastcall) == 0)
    return 0;

  multi->timer_lastcall = multi->timetree->key;

  return multi->timer_cb(multi, timeout_ms, multi->timer_userp);
}
