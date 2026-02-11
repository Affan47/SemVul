ev_periodic_stop (EV_P_ ev_periodic *w)
{
  clear_pending (EV_A_ (W)w);
  if (expect_false (!ev_is_active (w)))
    return;

  EV_FREQUENT_CHECK;

  {
    int active = ev_active (w);

    assert (("libev: internal periodic heap corruption", ANHE_w (periodics [active]) == (WT)w));

    --periodiccnt;

    if (expect_true (active < periodiccnt + HEAP0))
      {
        periodics [active] = periodics [periodiccnt + HEAP0];
        adjustheap (periodics, periodiccnt, active);
      }
  }

  ev_stop (EV_A_ (W)w);

  EV_FREQUENT_CHECK;
}
