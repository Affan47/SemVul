static void check_unneeded_dependencies(Unit *u) {

        static const UnitDependency deps[] = {
                UNIT_REQUIRES,
                UNIT_REQUISITE,
                UNIT_WANTS,
                UNIT_BINDS_TO,
        };
        size_t j;

        assert(u);


        for (j = 0; j < ELEMENTSOF(deps); j++) {
                Unit *other;
                Iterator i;
                void *v;

                HASHMAP_FOREACH_KEY(v, other, u->dependencies[deps[j]], i)
                        unit_submit_to_stop_when_unneeded_queue(other);
        }
}
