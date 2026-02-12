int epo_fillpage(gx_device *dev, gs_gstate * pgs, gx_device_color *pdevc)
{
    erasepage_subclass_data *data = (erasepage_subclass_data *)dev->subclass_data;

    if (gs_debug_c(gs_debug_flag_epo_install_only)) {
        return default_subclass_fillpage(dev, pgs, pdevc);
    }


    if (!color_is_pure(pdevc)) {
        DPRINTF(dev->memory, "epo_fillpage(), color is not pure, uninstalling\n");
        gx_device_unsubclass(dev);
        return dev_proc(dev, fillpage)(dev, pgs, pdevc);
    }


    data->last_color = pdevc->colors.pure;

    DPRINTF(dev->memory, "Swallowing fillpage\n");
    return 0;
}
