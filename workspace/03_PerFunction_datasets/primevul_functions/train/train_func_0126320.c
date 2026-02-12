int unit_start(Unit *u) {
        UnitActiveState state;
        Unit *following;
        int r;

        assert(u);


        state = unit_active_state(u);
        if (UNIT_IS_ACTIVE_OR_RELOADING(state))
                return -EALREADY;


        if (u->load_state != UNIT_LOADED)
                return -EINVAL;


        if (UNIT_VTABLE(u)->once_only && dual_timestamp_is_set(&u->inactive_enter_timestamp))
                return -ESTALE;


        if (state != UNIT_ACTIVATING &&
            !unit_test_condition(u)) {


                r = unit_test_start_limit(u);
                if (r < 0)
                        return r;

                return log_unit_debug_errno(u, SYNTHETIC_ERRNO(ECOMM), "Starting requested but condition failed. Not starting unit.");
        }


        if (state != UNIT_ACTIVATING &&
            !unit_test_assert(u))
                return log_unit_notice_errno(u, SYNTHETIC_ERRNO(EPROTO), "Starting requested but asserts failed.");


        if (!unit_supported(u))
                return -EOPNOTSUPP;


        if (!unit_verify_deps(u))
                return -ENOLINK;


        following = unit_following(u);
        if (following) {
                log_unit_debug(u, "Redirecting start request from %s to %s.", u->id, following->id);
                return unit_start(following);
        }


        if (!UNIT_VTABLE(u)->start)
                return -EBADR;


        unit_add_to_dbus_queue(u);

        return UNIT_VTABLE(u)->start(u);
}
