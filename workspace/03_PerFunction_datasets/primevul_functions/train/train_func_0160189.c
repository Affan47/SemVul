void manager_check_finished(Manager *m) {
        Unit *u = NULL;
        Iterator i;

        assert(m);

        if (hashmap_size(m->jobs) > 0) {

                if (m->jobs_in_progress_event_source)
                        sd_event_source_set_time(m->jobs_in_progress_event_source, now(CLOCK_MONOTONIC) + JOBS_IN_PROGRESS_WAIT_USEC);

                return;
        }

        manager_flip_auto_status(m, false);


        m->idle_pipe_event_source = sd_event_source_unref(m->idle_pipe_event_source);
        manager_close_idle_pipe(m);


        m->confirm_spawn = false;


        manager_close_ask_password(m);


        manager_set_first_boot(m, false);

        if (dual_timestamp_is_set(&m->finish_timestamp))
                return;

        dual_timestamp_get(&m->finish_timestamp);

        manager_notify_finished(m);

        SET_FOREACH(u, m->startup_units, i)
                if (u->cgroup_path)
                        cgroup_context_apply(unit_get_cgroup_context(u), unit_get_cgroup_mask(u), u->cgroup_path, manager_state(m));
}
