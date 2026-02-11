loop_init (EV_P_ unsigned int flags)
{
  if (!backend)
    {
      origflags = flags;

#if EV_USE_REALTIME
      if (!have_realtime)
        {
          struct timespec ts;

          if (!clock_gettime (CLOCK_REALTIME, &ts))
            have_realtime = 1;
        }
#endif

#if EV_USE_MONOTONIC
      if (!have_monotonic)
        {
          struct timespec ts;

          if (!clock_gettime (CLOCK_MONOTONIC, &ts))
            have_monotonic = 1;
        }
#endif


#ifndef _WIN32
      if (flags & EVFLAG_FORKCHECK)
        curpid = getpid ();
#endif

      if (!(flags & EVFLAG_NOENV)
          && !enable_secure ()
          && getenv ("LIBEV_FLAGS"))
        flags = atoi (getenv ("LIBEV_FLAGS"));

      ev_rt_now          = ev_time ();
      mn_now             = get_clock ();
      now_floor          = mn_now;
      rtmn_diff          = ev_rt_now - mn_now;
#if EV_FEATURE_API
      invoke_cb          = ev_invoke_pending;
#endif

      io_blocktime       = 0.;
      timeout_blocktime  = 0.;
      backend            = 0;
      backend_fd         = -1;
      sig_pending        = 0;
#if EV_ASYNC_ENABLE
      async_pending      = 0;
#endif
      pipe_write_skipped = 0;
      pipe_write_wanted  = 0;
#if EV_USE_INOTIFY
      fs_fd              = flags & EVFLAG_NOINOTIFY ? -1 : -2;
#endif
#if EV_USE_SIGNALFD
      sigfd              = flags & EVFLAG_SIGNALFD  ? -2 : -1;
#endif

      if (!(flags & EVBACKEND_MASK))
        flags |= ev_recommended_backends ();

#if EV_USE_IOCP
      if (!backend && (flags & EVBACKEND_IOCP  )) backend = iocp_init   (EV_A_ flags);
#endif
#if EV_USE_PORT
      if (!backend && (flags & EVBACKEND_PORT  )) backend = port_init   (EV_A_ flags);
#endif
#if EV_USE_KQUEUE
      if (!backend && (flags & EVBACKEND_KQUEUE)) backend = kqueue_init (EV_A_ flags);
#endif
#if EV_USE_EPOLL
      if (!backend && (flags & EVBACKEND_EPOLL )) backend = epoll_init  (EV_A_ flags);
#endif
#if EV_USE_POLL
      if (!backend && (flags & EVBACKEND_POLL  )) backend = poll_init   (EV_A_ flags);
#endif
#if EV_USE_SELECT
      if (!backend && (flags & EVBACKEND_SELECT)) backend = select_init (EV_A_ flags);
#endif

      ev_prepare_init (&pending_w, pendingcb);

#if EV_SIGNAL_ENABLE || EV_ASYNC_ENABLE
      ev_init (&pipe_w, pipecb);
      ev_set_priority (&pipe_w, EV_MAXPRI);
#endif
    }
}
