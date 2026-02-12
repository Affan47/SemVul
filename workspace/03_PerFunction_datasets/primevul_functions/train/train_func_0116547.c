int unit_start(Unit *u) {
        UnitActiveState state;
        Unit *following;

        assert(u);

        if (u->load_state != UNIT_LOADED)
                return -EINVAL;


        state = unit_active_state(u);
        if (UNIT_IS_ACTIVE_OR_RELOADING(state))
                return -EALREADY;


        if (state != UNIT_ACTIVATING &&
            !unit_condition_test(u)) {
                log_debug_unit(u->id, "Starting of %s requested but condition failed. Ignoring.", u->id);
                return -EALREADY;
        }


        following = unit_following(u);
        if (following) {
                log_debug_unit(u->id, "Redirecting start request from %s to %s.",
                               u->id, following->id);
                return unit_start(following);
        }

        unit_status_log_starting_stopping_reloading(u, JOB_START);
        unit_status_print_starting_stopping(u, JOB_START);


        if (!UNIT_VTABLE(u)->start)
                return -EBADR;


        unit_add_to_dbus_queue(u);

        return UNIT_VTABLE(u)->start(u);
}
