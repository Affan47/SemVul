bool unit_is_pristine(Unit *u) {
        assert(u);


        return !(!IN_SET(u->load_state, UNIT_NOT_FOUND, UNIT_LOADED) ||
                 u->fragment_path ||
                 u->source_path ||
                 !strv_isempty(u->dropin_paths) ||
                 u->job ||
                 u->merged_into);
}
