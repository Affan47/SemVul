void mg_timer_poll(int64_t now_ms) {

  struct mg_timer *t, *tmp;
  static int64_t oldnow;
  if (oldnow > now_ms) {
    for (t = g_timers; t != NULL; t = t->next) t->expire = 0;
  }
  oldnow = now_ms;

  for (t = g_timers; t != NULL; t = tmp) {
    tmp = t->next;
    if (t->expire == 0) t->expire = now_ms + t->period_ms;
    if (t->expire > now_ms) continue;
    t->fn(t->arg);


    t->expire = now_ms - t->expire > t->period_ms ? now_ms + t->period_ms
                                                  : t->expire + t->period_ms;
    if (!(t->flags & MG_TIMER_REPEAT)) mg_timer_free(t);
  }
}
