int unit_load_fragment_and_dropin_optional(Unit *u) {
        int r;

        assert(u);


        r = unit_load_fragment(u);
        if (r < 0)
                return r;

        if (u->load_state == UNIT_STUB)
                u->load_state = UNIT_LOADED;


        return unit_load_dropin(unit_follow_merge(u));
}
