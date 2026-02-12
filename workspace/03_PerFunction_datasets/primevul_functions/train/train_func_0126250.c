static void merge_dependencies(Unit *u, Unit *other, const char *other_id, UnitDependency d) {
        Iterator i;
        Unit *back;
        void *v;
        int r;


        assert(u);
        assert(other);
        assert(d < _UNIT_DEPENDENCY_MAX);


        HASHMAP_FOREACH_KEY(v, back, other->dependencies[d], i) {
                UnitDependency k;


                for (k = 0; k < _UNIT_DEPENDENCY_MAX; k++) {
                        if (back == u) {

                                if (hashmap_remove(back->dependencies[k], other))
                                        maybe_warn_about_dependency(u, other_id, k);
                        } else {
                                UnitDependencyInfo di_u, di_other, di_merged;


                                di_other.data = hashmap_get(back->dependencies[k], other);
                                if (!di_other.data)
                                        continue;

                                di_u.data = hashmap_get(back->dependencies[k], u);

                                di_merged = (UnitDependencyInfo) {
                                        .origin_mask = di_u.origin_mask | di_other.origin_mask,
                                        .destination_mask = di_u.destination_mask | di_other.destination_mask,
                                };

                                r = hashmap_remove_and_replace(back->dependencies[k], other, u, di_merged.data);
                                if (r < 0)
                                        log_warning_errno(r, "Failed to remove/replace: back=%s other=%s u=%s: %m", back->id, other_id, u->id);
                                assert(r >= 0);


                        }
                }

        }


        back = hashmap_remove(other->dependencies[d], u);
        if (back)
                maybe_warn_about_dependency(u, other_id, d);


        assert_se(hashmap_complete_move(&u->dependencies[d], &other->dependencies[d]) == 0);

        other->dependencies[d] = hashmap_free(other->dependencies[d]);
}
