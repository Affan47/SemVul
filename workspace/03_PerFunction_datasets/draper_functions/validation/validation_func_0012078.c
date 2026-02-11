plane_device_init(gx_device_plane_extract *edev, gx_device *target,
    gx_device *plane_dev, const gx_render_plane_t *render_plane, bool clear)
{

    if (render_plane->depth > plane_dev->color_info.depth)
        return_error(gs_error_rangecheck);
    gx_device_init((gx_device *)edev,
                   (const gx_device *)&gs_plane_extract_device,
                   edev->memory, true);
    check_device_separable((gx_device *)edev);
    gx_device_forward_fill_in_procs((gx_device_forward *)edev);
    gx_device_set_target((gx_device_forward *)edev, target);
    gx_device_copy_params((gx_device *)edev, target);
    edev->plane_dev = plane_dev;
    edev->plane = *render_plane;
    plane_open_device((gx_device *)edev);
    if (clear) {
        dev_proc(plane_dev, fill_rectangle)
            (plane_dev, 0, 0, plane_dev->width, plane_dev->height,
             edev->plane_white);
        edev->any_marks = false;
    }
    return 0;
}
