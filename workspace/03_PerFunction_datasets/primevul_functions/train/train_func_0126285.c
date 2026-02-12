static const char* unit_drop_in_dir(Unit *u, UnitWriteFlags flags) {
        assert(u);

        if (UNIT_WRITE_FLAGS_NOOP(flags))
                return NULL;

        if (u->transient)
                return u->manager->lookup_paths.transient;

        if (flags & UNIT_PERSISTENT)
                return u->manager->lookup_paths.persistent_control;

        if (flags & UNIT_RUNTIME)
                return u->manager->lookup_paths.runtime_control;

        return NULL;
}
