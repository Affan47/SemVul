static int manager_coldplug(Manager *m) {
        int r = 0, q;
        Iterator i;
        Unit *u;
        char *k;

        assert(m);


        HASHMAP_FOREACH_KEY(u, k, m->units, i) {


                if (u->id != k)
                        continue;

                if ((q = unit_coldplug(u)) < 0)
                        r = q;
        }

        return r;
}
