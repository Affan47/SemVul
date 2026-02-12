(*get_decode_color(gx_device * dev))(gx_device *, gx_color_index, gx_color_value *)
{

    if (dev_proc(dev, decode_color) != 0)
        return dev_proc(dev, decode_color);


    if (dev_proc(dev, map_color_rgb) != 0) {


        if (is_like_DeviceRGB(dev))
            return dev_proc(dev, map_color_rgb);


        if (colors_are_separable_and_linear(&dev->color_info))
            return &gx_default_decode_color;


        if ( dev->color_info.num_components == 1 &&
             dev->color_info.gray_index == 0       )
            return dev->color_info.polarity == GX_CINFO_POLARITY_ADDITIVE
                       ? &gx_default_1_add_decode_color
                       : &gx_default_1_sub_decode_color;


        if (is_like_DeviceCMYK(dev)) {
            if (dev_proc(dev, map_color_rgb) == cmyk_1bit_map_color_rgb)
                return &gx_1bit_cmyk_decode_color;
            else
                return &gx_default_cmyk_decode_color;
        }
    }


    if (colors_are_separable_and_linear(&dev->color_info))
        return &gx_default_decode_color;
    else
        return &gx_error_decode_color;
}
