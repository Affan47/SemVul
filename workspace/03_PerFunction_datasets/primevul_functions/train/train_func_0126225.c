const char *unit_label_path(Unit *u) {
        const char *p;


        p = u->source_path ?: u->fragment_path;
        if (!p)
                return NULL;


        if (path_equal(p, "/dev/null"))
                return NULL;

        return p;
}
