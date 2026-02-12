int unit_failure_action_exit_status(Unit *u) {
        int r;

        assert(u);


        if (u->failure_action_exit_status >= 0)
                return u->failure_action_exit_status;

        r = unit_exit_status(u);
        if (r == -EBADE)
                return 255;

        return r;
}
