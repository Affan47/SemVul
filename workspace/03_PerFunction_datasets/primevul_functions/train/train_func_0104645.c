int manager_startup(Manager *m, FILE *serialization, FDSet *fds) {
        int r, q;

        assert(m);

        r = lookup_paths_init(&m->lookup_paths, m->unit_file_scope, 0, NULL);
        if (r < 0)
                return r;


        r = mkdir_p_label(m->lookup_paths.transient, 0755);
        if (r < 0)
                return r;

        dual_timestamp_get(&m->generators_start_timestamp);
        r = manager_run_generators(m);
        dual_timestamp_get(&m->generators_finish_timestamp);
        if (r < 0)
                return r;

        lookup_paths_reduce(&m->lookup_paths);
        manager_build_unit_path_cache(m);


        if (serialization)
                m->n_reloading++;


        dual_timestamp_get(&m->units_load_start_timestamp);
        manager_enumerate(m);
        dual_timestamp_get(&m->units_load_finish_timestamp);


        if (serialization)
                r = manager_deserialize(m, serialization, fds);


        manager_distribute_fds(m, fds);


        q = manager_setup_notify(m);
        if (q < 0 && r == 0)
                r = q;

        q = manager_setup_cgroups_agent(m);
        if (q < 0 && r == 0)
                r = q;

        q = manager_setup_user_lookup_fd(m);
        if (q < 0 && r == 0)
                r = q;


        (void) manager_connect_bus(m, !!serialization);

        (void) bus_track_coldplug(m, &m->subscribed, false, m->deserialized_subscribed);
        m->deserialized_subscribed = strv_free(m->deserialized_subscribed);


        manager_coldplug(m);


        dynamic_user_vacuum(m, true);


        manager_vacuum_uid_refs(m);
        manager_vacuum_gid_refs(m);

        if (serialization) {
                assert(m->n_reloading > 0);
                m->n_reloading--;


                m->send_reloading_done = true;
        }

        return r;
}
