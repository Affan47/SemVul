uv__timer_cb(EV_P_ ev_timer* w, int revents) {
  uv_timer_t* timer = w->data;

  if (!ev_is_active(w)) {
    ev_ref(EV_A);
  }

  if (timer->timer_cb) {
    timer->timer_cb(timer, 0);
  }
}
