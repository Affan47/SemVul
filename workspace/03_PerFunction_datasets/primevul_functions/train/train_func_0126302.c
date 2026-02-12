void unit_unwatch_pid(Unit *u, pid_t pid) {
        Unit **array;

        assert(u);
        assert(pid_is_valid(pid));


        (void) hashmap_remove_value(u->manager->watch_pids, PID_TO_PTR(pid), u);


        array = hashmap_get(u->manager->watch_pids, PID_TO_PTR(-pid));
        if (array) {
                size_t n, m = 0;


                for (n = 0; array[n]; n++)
                        if (array[n] != u)
                                array[m++] = array[n];
                array[m] = NULL;

                if (m == 0) {

                        assert(hashmap_remove(u->manager->watch_pids, PID_TO_PTR(-pid)) == array);
                        free(array);
                }
        }

        (void) set_remove(u->pids, PID_TO_PTR(pid));
}
