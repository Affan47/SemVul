int unit_enqueue_rewatch_pids(Unit *u) {
        int r;

        assert(u);

        if (!u->cgroup_path)
                return -ENOENT;

        r = cg_unified_controller(SYSTEMD_CGROUP_CONTROLLER);
        if (r < 0)
                return r;
        if (r > 0)
                return 0;


        if (!u->rewatch_pids_event_source) {
                _cleanup_(sd_event_source_unrefp) sd_event_source *s = NULL;

                r = sd_event_add_defer(u->manager->event, &s, on_rewatch_pids_event, u);
                if (r < 0)
                        return log_error_errno(r, "Failed to allocate event source for tidying watched PIDs: %m");

                r = sd_event_source_set_priority(s, SD_EVENT_PRIORITY_IDLE);
                if (r < 0)
                        return log_error_errno(r, "Failed to adjust priority of event source for tidying watched PIDs: m");

                (void) sd_event_source_set_description(s, "tidy-watch-pids");

                u->rewatch_pids_event_source = TAKE_PTR(s);
        }

        r = sd_event_source_set_enabled(u->rewatch_pids_event_source, SD_EVENT_ONESHOT);
        if (r < 0)
                return log_error_errno(r, "Failed to enable event source for tidying watched PIDs: %m");

        return 0;
}
