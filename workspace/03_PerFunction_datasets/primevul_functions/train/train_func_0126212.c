static void unit_emit_audit_start(Unit *u) {
        assert(u);

        if (u->type != UNIT_SERVICE)
                return;


        manager_send_unit_audit(u->manager, u, AUDIT_SERVICE_START, true);
        u->in_audit = true;
}
