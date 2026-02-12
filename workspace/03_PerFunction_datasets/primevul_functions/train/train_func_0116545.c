static void unit_check_unneeded(Unit *u) {
        Iterator i;
        Unit *other;

        assert(u);


        if (!u->stop_when_unneeded)
                return;

        if (!UNIT_IS_ACTIVE_OR_ACTIVATING(unit_active_state(u)))
                return;

        SET_FOREACH(other, u->dependencies[UNIT_REQUIRED_BY], i)
                if (unit_active_or_pending(other))
                        return;

        SET_FOREACH(other, u->dependencies[UNIT_REQUIRED_BY_OVERRIDABLE], i)
                if (unit_active_or_pending(other))
                        return;

        SET_FOREACH(other, u->dependencies[UNIT_WANTED_BY], i)
                if (unit_active_or_pending(other))
                        return;

        SET_FOREACH(other, u->dependencies[UNIT_BOUND_BY], i)
                if (unit_active_or_pending(other))
                        return;

        log_info_unit(u->id, "Service %s is not needed anymore. Stopping.", u->id);


        manager_add_job(u->manager, JOB_STOP, u, JOB_FAIL, true, NULL, NULL);
}
