epo_check_and_install(gx_device *dev)
{
    int code = 0;
    bool is_installed;
    bool can_optimize = false;


    if (gs_debug_c(gs_debug_flag_epo_disable)) {
        return code;
    }

    DPRINTF1(dev->memory, "current device is %s\n", dev->dname);

    is_installed = is_device_installed(dev, EPO_DEVICENAME);

    if (is_installed) {
        DPRINTF1(dev->memory, "device %s already installed\n", EPO_DEVICENAME);


        if (dev->child) {
            can_optimize = device_wants_optimization(dev->child);
        }
        if (!can_optimize) {
            DPRINTF1(dev->memory, "child %s can't be optimized, uninstalling\n", dev->child->dname);


            gx_device_unsubclass(dev);
            return code;
        }
    } else {
        can_optimize = device_wants_optimization(dev);
    }


    if (is_installed) {
        return code;
    }


    if (!can_optimize) {
        DPRINTF(dev->memory, "device doesn't want optimization, not installing\n");
        return code;
    }


    code = gx_device_subclass(dev, (gx_device *)&gs_epo_device, sizeof(erasepage_subclass_data));
    if (code < 0) {
        DPRINTF1(dev->memory, "ERROR installing device %s\n", EPO_DEVICENAME);
        return code;
    }

    DPRINTF1(dev->memory, "SUCCESS installed device %s\n", dev->dname);
    return code;
}
