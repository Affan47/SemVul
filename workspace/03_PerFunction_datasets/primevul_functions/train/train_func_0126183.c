static bool unit_verify_deps(Unit *u) {
        Unit *other;
        Iterator j;
        void *v;

        assert(u);


        HASHMAP_FOREACH_KEY(v, other, u->dependencies[UNIT_BINDS_TO], j) {

                if (!hashmap_contains(u->dependencies[UNIT_AFTER], other))
                        continue;

                if (!UNIT_IS_ACTIVE_OR_RELOADING(unit_active_state(other))) {
                        log_unit_notice(u, "Bound to unit %s, but unit isn't active.", other->id);
                        return false;
                }
        }

        return true;
}
