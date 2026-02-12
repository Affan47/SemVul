int unit_merge(Unit *u, Unit *other) {
        UnitDependency d;
        const char *other_id = NULL;
        int r;

        assert(u);
        assert(other);
        assert(u->manager == other->manager);
        assert(u->type != _UNIT_TYPE_INVALID);

        other = unit_follow_merge(other);

        if (other == u)
                return 0;

        if (u->type != other->type)
                return -EINVAL;

        if (!u->instance != !other->instance)
                return -EINVAL;

        if (!unit_type_may_alias(u->type))
                return -EEXIST;

        if (!IN_SET(other->load_state, UNIT_STUB, UNIT_NOT_FOUND))
                return -EEXIST;

        if (other->job)
                return -EEXIST;

        if (other->nop_job)
                return -EEXIST;

        if (!UNIT_IS_INACTIVE_OR_FAILED(unit_active_state(other)))
                return -EEXIST;

        if (other->id)
                other_id = strdupa(other->id);


        for (d = 0; d < _UNIT_DEPENDENCY_MAX; d++) {
                r = reserve_dependencies(u, other, d);


                if (r < 0)
                        return r;
        }


        r = merge_names(u, other);
        if (r < 0)
                return r;


        while (other->refs_by_target)
                unit_ref_set(other->refs_by_target, other->refs_by_target->source, u);


        for (d = 0; d < _UNIT_DEPENDENCY_MAX; d++)
                merge_dependencies(u, other, other_id, d);

        other->load_state = UNIT_MERGED;
        other->merged_into = u;


        if (other->load_state != UNIT_STUB)
                if (UNIT_VTABLE(other)->done)
                        UNIT_VTABLE(other)->done(other);

        unit_add_to_dbus_queue(u);
        unit_add_to_cleanup_queue(other);

        return 0;
}
