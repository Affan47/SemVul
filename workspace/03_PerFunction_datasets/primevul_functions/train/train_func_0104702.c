int manager_reload(Manager *m) {
        int r, q;
        _cleanup_fclose_ FILE *f = NULL;
        _cleanup_fdset_free_ FDSet *fds = NULL;

        assert(m);

        r = manager_open_serialization(m, &f);
        if (r < 0)
                return r;

        m->n_reloading++;
        bus_manager_send_reloading(m, true);

        fds = fdset_new();
        if (!fds) {
                m->n_reloading--;
                return -ENOMEM;
        }

        r = manager_serialize(m, f, fds, false);
        if (r < 0) {
                m->n_reloading--;
                return r;
        }

        if (fseeko(f, 0, SEEK_SET) < 0) {
                m->n_reloading--;
                return -errno;
        }


        manager_clear_jobs_and_units(m);
        lookup_paths_flush_generator(&m->lookup_paths);
        lookup_paths_free(&m->lookup_paths);
        dynamic_user_vacuum(m, false);
        m->uid_refs = hashmap_free(m->uid_refs);
        m->gid_refs = hashmap_free(m->gid_refs);

        q = lookup_paths_init(&m->lookup_paths, m->unit_file_scope, 0, NULL);
        if (q < 0 && r >= 0)
                r = q;


        q = manager_run_generators(m);
        if (q < 0 && r >= 0)
                r = q;

        lookup_paths_reduce(&m->lookup_paths);
        manager_build_unit_path_cache(m);


        manager_enumerate(m);


        q = manager_deserialize(m, f, fds);
        if (q < 0 && r >= 0)
                r = q;

        fclose(f);
        f = NULL;


        q = manager_setup_notify(m);
        if (q < 0 && r >= 0)
                r = q;

        q = manager_setup_cgroups_agent(m);
        if (q < 0 && r >= 0)
                r = q;

        q = manager_setup_user_lookup_fd(m);
        if (q < 0 && r >= 0)
                r = q;


        manager_coldplug(m);


        dynamic_user_vacuum(m, true);


        manager_vacuum_uid_refs(m);
        manager_vacuum_gid_refs(m);


        if (m->api_bus)
                manager_sync_bus_names(m, m->api_bus);

        assert(m->n_reloading > 0);
        m->n_reloading--;

        m->send_reloading_done = true;

        return r;
}
