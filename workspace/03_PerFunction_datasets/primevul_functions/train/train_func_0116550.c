int unit_watch_bus_name(Unit *u, const char *name) {
        assert(u);
        assert(name);


        return hashmap_put(u->manager->watch_bus, name, u);
}
