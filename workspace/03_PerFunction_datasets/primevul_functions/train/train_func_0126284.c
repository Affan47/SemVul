int unit_watch_pid(Unit *u, pid_t pid, bool exclusive) {
        int r;

        assert(u);
        assert(pid_is_valid(pid));


        if (exclusive)
                manager_unwatch_pid(u->manager, pid);

        r = set_ensure_allocated(&u->pids, NULL);
        if (r < 0)
                return r;

        r = hashmap_ensure_allocated(&u->manager->watch_pids, NULL);
        if (r < 0)
                return r;


        r = hashmap_put(u->manager->watch_pids, PID_TO_PTR(pid), u);
        if (r == -EEXIST)  {
                Unit **array;
                bool found = false;
                size_t n = 0;


                array = hashmap_get(u->manager->watch_pids, PID_TO_PTR(-pid));
                if (array)
                        for (; array[n]; n++)
                                if (array[n] == u)
                                        found = true;

                if (found)
                        r = 0;
                else {
                        Unit **new_array;


                        new_array = new(Unit*, n + 2);
                        if (!new_array)
                                return -ENOMEM;

                        memcpy_safe(new_array, array, sizeof(Unit*) * n);
                        new_array[n] = u;
                        new_array[n+1] = NULL;


                        r = hashmap_replace(u->manager->watch_pids, PID_TO_PTR(-pid), new_array);
                        if (r < 0) {
                                free(new_array);
                                return r;
                        }

                        free(array);
                }
        } else if (r < 0)
                return r;

        r = set_put(u->pids, PID_TO_PTR(pid));
        if (r < 0)
                return r;

        return 0;
}
