int unit_watch_all_pids(Unit *u) {
        assert(u);

        if (!u->cgroup_path)
                return -ENOENT;


        return watch_pids_in_path(u, u->cgroup_path);
}
