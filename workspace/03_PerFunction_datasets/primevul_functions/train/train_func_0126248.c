int unit_add_default_target_dependency(Unit *u, Unit *target) {
        assert(u);
        assert(target);

        if (target->type != UNIT_TARGET)
                return 0;


        if (u->load_state != UNIT_LOADED ||
            target->load_state != UNIT_LOADED)
                return 0;


        if (!u->default_dependencies ||
            !target->default_dependencies)
                return 0;


        if (hashmap_get(target->dependencies[UNIT_BEFORE], u))
                return 0;

        return unit_add_dependency(target, UNIT_AFTER, u, true, UNIT_DEPENDENCY_DEFAULT);
}
