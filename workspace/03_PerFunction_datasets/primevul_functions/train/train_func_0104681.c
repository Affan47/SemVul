static void manager_clean_environment(Manager *m) {
        assert(m);


        strv_env_unset_many(
                        m->environment,
                        "NOTIFY_SOCKET",
                        "MAINPID",
                        "MANAGERPID",
                        "LISTEN_PID",
                        "LISTEN_FDS",
                        "LISTEN_FDNAMES",
                        "WATCHDOG_PID",
                        "WATCHDOG_USEC",
                        NULL);
}
