bool unit_inactive_or_pending(Unit *u) {
        assert(u);


        if (UNIT_IS_INACTIVE_OR_DEACTIVATING(unit_active_state(u)))
                return true;

        if (unit_stop_pending(u))
                return true;

        return false;
}
