void unit_notify(Unit *u, UnitActiveState os, UnitActiveState ns, UnitNotifyFlags flags) {
        const char *reason;
        Manager *m;

        assert(u);
        assert(os < _UNIT_ACTIVE_STATE_MAX);
        assert(ns < _UNIT_ACTIVE_STATE_MAX);


        m = u->manager;


        unit_add_to_dbus_queue(u);


        if (!MANAGER_IS_RELOADING(m)) {
                dual_timestamp_get(&u->state_change_timestamp);

                if (UNIT_IS_INACTIVE_OR_FAILED(os) && !UNIT_IS_INACTIVE_OR_FAILED(ns))
                        u->inactive_exit_timestamp = u->state_change_timestamp;
                else if (!UNIT_IS_INACTIVE_OR_FAILED(os) && UNIT_IS_INACTIVE_OR_FAILED(ns))
                        u->inactive_enter_timestamp = u->state_change_timestamp;

                if (!UNIT_IS_ACTIVE_OR_RELOADING(os) && UNIT_IS_ACTIVE_OR_RELOADING(ns))
                        u->active_enter_timestamp = u->state_change_timestamp;
                else if (UNIT_IS_ACTIVE_OR_RELOADING(os) && !UNIT_IS_ACTIVE_OR_RELOADING(ns))
                        u->active_exit_timestamp = u->state_change_timestamp;
        }


        (void) manager_update_failed_units(m, u, ns == UNIT_FAILED);


        if (UNIT_IS_INACTIVE_OR_FAILED(ns)) {
                unit_prune_cgroup(u);
                unit_unlink_state_files(u);
        }

        unit_update_on_console(u);

        if (!MANAGER_IS_RELOADING(m)) {
                bool unexpected;


                if (u->job)
                        unexpected = unit_process_job(u->job, ns, flags);
                else
                        unexpected = true;


                if (unexpected) {
                        if (UNIT_IS_INACTIVE_OR_FAILED(os) && UNIT_IS_ACTIVE_OR_ACTIVATING(ns))
                                retroactively_start_dependencies(u);
                        else if (UNIT_IS_ACTIVE_OR_ACTIVATING(os) && UNIT_IS_INACTIVE_OR_DEACTIVATING(ns))
                                retroactively_stop_dependencies(u);
                }


                if (UNIT_IS_INACTIVE_OR_FAILED(ns))
                        check_unneeded_dependencies(u);

                if (ns != os && ns == UNIT_FAILED) {
                        log_unit_debug(u, "Unit entered failed state.");

                        if (!(flags & UNIT_NOTIFY_WILL_AUTO_RESTART))
                                unit_start_on_failure(u);
                }

                if (UNIT_IS_ACTIVE_OR_RELOADING(ns) && !UNIT_IS_ACTIVE_OR_RELOADING(os)) {


                        unit_emit_audit_start(u);
                        manager_send_unit_plymouth(m, u);
                }

                if (UNIT_IS_INACTIVE_OR_FAILED(ns) && !UNIT_IS_INACTIVE_OR_FAILED(os)) {


                        unit_emit_audit_stop(u, ns);
                        unit_log_resources(u);
                }
        }

        manager_recheck_journal(m);
        manager_recheck_dbus(m);

        unit_trigger_notify(u);

        if (!MANAGER_IS_RELOADING(m)) {

                unit_submit_to_stop_when_unneeded_queue(u);


                unit_check_binds_to(u);

                if (os != UNIT_FAILED && ns == UNIT_FAILED) {
                        reason = strjoina("unit ", u->id, " failed");
                        emergency_action(m, u->failure_action, 0, u->reboot_arg, unit_failure_action_exit_status(u), reason);
                } else if (!UNIT_IS_INACTIVE_OR_FAILED(os) && ns == UNIT_INACTIVE) {
                        reason = strjoina("unit ", u->id, " succeeded");
                        emergency_action(m, u->success_action, 0, u->reboot_arg, unit_success_action_exit_status(u), reason);
                }
        }

        unit_add_to_gc_queue(u);
}
