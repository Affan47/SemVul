void manager_check_finished(Manager *m) {
        assert(m);

        if (MANAGER_IS_RELOADING(m))
                return;


        if (m->exit_code != MANAGER_OK)
                return;

        if (hashmap_size(m->jobs) > 0) {
                if (m->jobs_in_progress_event_source)

                        (void) sd_event_source_set_time(m->jobs_in_progress_event_source, now(CLOCK_MONOTONIC) + JOBS_IN_PROGRESS_WAIT_USEC);

                return;
        }

        manager_flip_auto_status(m, false);


        manager_close_idle_pipe(m);


        m->confirm_spawn = false;


        manager_close_ask_password(m);


        manager_set_first_boot(m, false);

        if (dual_timestamp_is_set(&m->finish_timestamp))
                return;

        dual_timestamp_get(&m->finish_timestamp);

        manager_notify_finished(m);

        manager_invalidate_startup_units(m);
}
