x_alt_map_color(gx_device * dev, gx_color_index color)
{
    gx_device_X_wrapper *xdev = (gx_device_X_wrapper *) dev;
    gx_device *tdev;
    gx_color_value rgb[3];
    gx_color_index cindex;
    int result;
    int code;

    if (color == gx_no_color_index)
        return color;
    if (color < 16) {
        cindex = ((gx_device_X_wrapper *) dev)->color_cache[color];
        if (cindex != gx_no_color_index)
            return cindex;
    }
    if ((code = get_dev_target(&tdev, dev)) < 0)
        return code;
    result = xdev->alt_map_color(dev, color, rgb);
    if (result >= 0)
        cindex = result;
    else
        cindex = dev_proc(tdev, map_rgb_color)(tdev, rgb);
    if (color < 16)
        ((gx_device_X_wrapper *) dev)->color_cache[color] = cindex;
    return cindex;
}
