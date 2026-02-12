epo_handle_erase_page(gx_device *dev)
{
    erasepage_subclass_data *data = (erasepage_subclass_data *)dev->subclass_data;
    int code = 0;

    if (gs_debug_c(gs_debug_flag_epo_install_only)) {
        gx_device_unsubclass(dev);
        DPRINTF1(dev->memory, "Uninstall erasepage, device=%s\n", dev->dname);
        return code;
    }

    DPRINTF1(dev->memory, "Do fillpage, Uninstall erasepage, device %s\n", dev->dname);


    if (dev->child) {
        code = dev_proc(dev->child, fill_rectangle)(dev->child,
                                                    0, 0,
                                                    dev->child->width,
                                                    dev->child->height,
                                                    data->last_color);
    }

    gx_device_unsubclass(dev);

    return code;
}
