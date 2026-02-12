int unit_success_action_exit_status(Unit *u) {
        int r;

        assert(u);


        if (u->success_action_exit_status >= 0)
                return u->success_action_exit_status;

        r = unit_exit_status(u);
        if (r == -EBADE)
                return 255;

        return r;
}
