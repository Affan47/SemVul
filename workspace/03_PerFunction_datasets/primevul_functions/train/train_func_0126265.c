bool unit_may_gc(Unit *u) {
        UnitActiveState state;
        int r;

        assert(u);


        if (u->job)
                return false;

        if (u->nop_job)
                return false;

        state = unit_active_state(u);


        if (UNIT_IS_INACTIVE_OR_FAILED(state) &&
            UNIT_VTABLE(u)->release_resources)
                UNIT_VTABLE(u)->release_resources(u);

        if (u->perpetual)
                return false;

        if (sd_bus_track_count(u->bus_track) > 0)
                return false;


        switch (u->collect_mode) {

        case COLLECT_INACTIVE:
                if (state != UNIT_INACTIVE)
                        return false;

                break;

        case COLLECT_INACTIVE_OR_FAILED:
                if (!IN_SET(state, UNIT_INACTIVE, UNIT_FAILED))
                        return false;

                break;

        default:
                assert_not_reached("Unknown garbage collection mode");
        }

        if (u->cgroup_path) {


                r = cg_is_empty_recursive(SYSTEMD_CGROUP_CONTROLLER, u->cgroup_path);
                if (r < 0)
                        log_unit_debug_errno(u, r, "Failed to determine whether cgroup %s is empty: %m", u->cgroup_path);
                if (r <= 0)
                        return false;
        }

        if (UNIT_VTABLE(u)->may_gc && !UNIT_VTABLE(u)->may_gc(u))
                return false;

        return true;
}
