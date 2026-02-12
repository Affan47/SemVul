static int manager_setup_signals(Manager *m) {
        struct sigaction sa = {
                .sa_handler = SIG_DFL,
                .sa_flags = SA_NOCLDSTOP|SA_RESTART,
        };
        sigset_t mask;
        int r;

        assert(m);

        assert_se(sigaction(SIGCHLD, &sa, NULL) == 0);


        assert_se(sigemptyset(&mask) == 0);
        sigset_add_many(&mask,
                        SIGCHLD,
                        SIGTERM,
                        SIGHUP,
                        SIGUSR1,
                        SIGUSR2,
                        SIGINT,
                        SIGWINCH,
                        SIGPWR,

                        SIGRTMIN+0,
                        SIGRTMIN+1,
                        SIGRTMIN+2,
                        SIGRTMIN+3,
                        SIGRTMIN+4,
                        SIGRTMIN+5,
                        SIGRTMIN+6,


                        SIGRTMIN+13,
                        SIGRTMIN+14,
                        SIGRTMIN+15,
                        SIGRTMIN+16,


                        SIGRTMIN+20,
                        SIGRTMIN+21,
                        SIGRTMIN+22,
                        SIGRTMIN+23,
                        SIGRTMIN+24,


#if !defined(__hppa64__) && !defined(__hppa__)


                        SIGRTMIN+26,
                        SIGRTMIN+27,
                        SIGRTMIN+28,
                        SIGRTMIN+29,


#endif
                        -1);
        assert_se(sigprocmask(SIG_SETMASK, &mask, NULL) == 0);

        m->signal_fd = signalfd(-1, &mask, SFD_NONBLOCK|SFD_CLOEXEC);
        if (m->signal_fd < 0)
                return -errno;

        r = sd_event_add_io(m->event, &m->signal_event_source, m->signal_fd, EPOLLIN, manager_dispatch_signal_fd, m);
        if (r < 0)
                return r;

        (void) sd_event_source_set_description(m->signal_event_source, "manager-signal");


        r = sd_event_source_set_priority(m->signal_event_source, SD_EVENT_PRIORITY_NORMAL-6);
        if (r < 0)
                return r;

        if (MANAGER_IS_SYSTEM(m))
                return enable_special_signals(m);

        return 0;
}
