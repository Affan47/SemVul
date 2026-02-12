int unit_watch_bus_name(Unit *u, const char *name) {
        int r;

        assert(u);
        assert(name);


        if (u->manager->api_bus) {


                r = unit_install_bus_match(u, u->manager->api_bus, name);
                if (r < 0)
                        return log_warning_errno(r, "Failed to subscribe to NameOwnerChanged signal for '%s': %m", name);
        }

        r = hashmap_put(u->manager->watch_bus, name, u);
        if (r < 0) {
                u->match_bus_slot = sd_bus_slot_unref(u->match_bus_slot);
                return log_warning_errno(r, "Failed to put bus name to hashmap: %m");
        }

        return 0;
}
