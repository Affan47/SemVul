int manager_startup(Manager *m, FILE *serialization, FDSet *fds) {
        int r, q;

        assert(m);

        dual_timestamp_get(&m->generators_start_timestamp);
        manager_run_generators(m);
        dual_timestamp_get(&m->generators_finish_timestamp);

        r = lookup_paths_init(
                        &m->lookup_paths, m->running_as, true,
                        m->generator_unit_path,
                        m->generator_unit_path_early,
                        m->generator_unit_path_late);
        if (r < 0)
                return r;

        manager_build_unit_path_cache(m);


        if (serialization)
                m->n_reloading ++;


        dual_timestamp_get(&m->units_load_start_timestamp);
        r = manager_enumerate(m);
        dual_timestamp_get(&m->units_load_finish_timestamp);


        if (serialization) {
                q = manager_deserialize(m, serialization, fds);
                if (q < 0)
                        r = q;
        }


        if (fdset_size(fds) > 0) {
                q = manager_distribute_fds(m, fds);
                if (q < 0)
                        r = q;
        }


        manager_setup_notify(m);


        manager_setup_kdbus(m);
        manager_connect_bus(m, !!serialization);


        q = manager_coldplug(m);
        if (q < 0)
                r = q;

        if (serialization) {
                assert(m->n_reloading > 0);
                m->n_reloading --;


                m->send_reloading_done = true;
        }

        return r;
}
