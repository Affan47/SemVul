long qemu_getrampagesize(void)
{
    long hpsize = LONG_MAX;
    long mainrampagesize;
    Object *memdev_root;

    if (mem_path) {
        mainrampagesize = qemu_mempath_getpagesize(mem_path);
    } else {
        mainrampagesize = getpagesize();
    }


    memdev_root = object_resolve_path("/objects", NULL);
    if (memdev_root) {
        object_child_foreach(memdev_root, find_max_supported_pagesize, &hpsize);
    }
    if (hpsize == LONG_MAX) {

        return mainrampagesize;
    }


    if (hpsize > mainrampagesize &&
        (nb_numa_nodes == 0 || numa_info[0].node_memdev == NULL)) {
        static bool warned;
        if (!warned) {
            error_report("Huge page support disabled (n/a for main memory).");
            warned = true;
        }
        return mainrampagesize;
    }

    return hpsize;
}
