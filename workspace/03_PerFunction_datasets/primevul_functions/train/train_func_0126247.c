void unit_export_state_files(Unit *u) {
        const ExecContext *c;

        assert(u);

        if (!u->id)
                return;

        if (!MANAGER_IS_SYSTEM(u->manager))
                return;

        if (MANAGER_IS_TEST_RUN(u->manager))
                return;


        (void) unit_export_invocation_id(u);

        c = unit_get_exec_context(u);
        if (c) {
                (void) unit_export_log_level_max(u, c);
                (void) unit_export_log_extra_fields(u, c);
                (void) unit_export_log_rate_limit_interval(u, c);
                (void) unit_export_log_rate_limit_burst(u, c);
        }
}
