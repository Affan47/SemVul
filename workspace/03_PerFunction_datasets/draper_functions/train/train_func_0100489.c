timer_del(void *b, char *id) {
  struct timer *t, *l;

  l = 0;
  t = timers;

  while (t) {
    if ((b == t->boundto) && !strcmp(id, t->id)) {
      if (l) {
        l->next = t->next;
      } else {
        timers = t->next;
      }

      debug("Timer %s will not be triggered (%d on the clock)",
            t->id, (t->time ? t->time - time(NULL) : 0));
      _timer_free(t);
      return 0;
    } else {
      l = t;
      t = t->next;
    }
  }

  return -1;
}
