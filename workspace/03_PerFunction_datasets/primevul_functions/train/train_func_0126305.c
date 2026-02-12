static void unit_check_binds_to(Unit *u) {
        _cleanup_(sd_bus_error_free) sd_bus_error error = SD_BUS_ERROR_NULL;
        bool stop = false;
        Unit *other;
        Iterator i;
        void *v;
        int r;

        assert(u);

        if (u->job)
                return;

        if (unit_active_state(u) != UNIT_ACTIVE)
                return;

        HASHMAP_FOREACH_KEY(v, other, u->dependencies[UNIT_BINDS_TO], i) {
                if (other->job)
                        continue;

                if (!other->coldplugged)

                        continue;

                if (!UNIT_IS_INACTIVE_OR_FAILED(unit_active_state(other)))
                        continue;

                stop = true;
                break;
        }

        if (!stop)
                return;


        if (!ratelimit_below(&u->auto_stop_ratelimit)) {
                log_unit_warning(u, "Unit is bound to inactive unit %s, but not stopping since we tried this too often recently.", other->id);
                return;
        }

        assert(other);
        log_unit_info(u, "Unit is bound to inactive unit %s. Stopping, too.", other->id);


        r = manager_add_job(u->manager, JOB_STOP, u, JOB_FAIL, NULL, &error, NULL);
        if (r < 0)
                log_unit_warning_errno(u, r, "Failed to enqueue stop job, ignoring: %s", bus_error_message(&error, r));
}
