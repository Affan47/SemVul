ManagerState manager_state(Manager *m) {
        Unit *u;

        assert(m);


        if (!dual_timestamp_is_set(&m->finish_timestamp)) {

                u = manager_get_unit(m, SPECIAL_BASIC_TARGET);
                if (!u || !UNIT_IS_ACTIVE_OR_RELOADING(unit_active_state(u)))
                        return MANAGER_INITIALIZING;

                return MANAGER_STARTING;
        }


        u = manager_get_unit(m, SPECIAL_SHUTDOWN_TARGET);
        if (u && u->job && IN_SET(u->job->type, JOB_START, JOB_RESTART, JOB_RELOAD_OR_START))
                return MANAGER_STOPPING;


        u = manager_get_unit(m, SPECIAL_RESCUE_TARGET);
        if (u && (UNIT_IS_ACTIVE_OR_ACTIVATING(unit_active_state(u)) ||
                  (u->job && IN_SET(u->job->type, JOB_START, JOB_RESTART, JOB_RELOAD_OR_START))))
                return MANAGER_MAINTENANCE;

        u = manager_get_unit(m, SPECIAL_EMERGENCY_TARGET);
        if (u && (UNIT_IS_ACTIVE_OR_ACTIVATING(unit_active_state(u)) ||
                  (u->job && IN_SET(u->job->type, JOB_START, JOB_RESTART, JOB_RELOAD_OR_START))))
                return MANAGER_MAINTENANCE;


        if (set_size(m->failed_units) > 0)
                return MANAGER_DEGRADED;

        return MANAGER_RUNNING;
}
