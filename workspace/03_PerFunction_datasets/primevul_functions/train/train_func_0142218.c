check_device_separable(gx_device * dev)
{
    int i, j;
    gx_device_color_info * pinfo = &(dev->color_info);
    int num_components = pinfo->num_components;
    byte comp_shift[GX_DEVICE_COLOR_MAX_COMPONENTS];
    byte comp_bits[GX_DEVICE_COLOR_MAX_COMPONENTS];
    gx_color_index comp_mask[GX_DEVICE_COLOR_MAX_COMPONENTS];
    gx_color_index color_index;
    gx_color_index current_bits = 0;
    gx_color_value colorants[GX_DEVICE_COLOR_MAX_COMPONENTS] = { 0 };


    if (pinfo->separable_and_linear != GX_CINFO_UNKNOWN_SEP_LIN)
        return;

    if (dev_proc(dev, encode_color) == NULL)
        return;


    if (pinfo->gray_index < num_components &&
        (!pinfo->dither_grays || pinfo->dither_grays != (pinfo->max_gray + 1)))
            return;
    if ((num_components > 1 || pinfo->gray_index != 0) &&
        (!pinfo->dither_colors || pinfo->dither_colors != (pinfo->max_color + 1)))
        return;


    if (!is_power_of_two(pinfo->dither_grays)
                    || !is_power_of_two(pinfo->dither_colors))
        return;


    color_index = dev_proc(dev, encode_color)(dev, colorants);
    if (color_index != 0)
        return;
    for (i = 0; i < num_components; i++) {

        for (j = 0; j < num_components; j++)
            colorants[j] = 0;
        colorants[i] = gx_max_color_value;
        color_index = dev_proc(dev, encode_color)(dev, colorants);
        if (color_index == 0)
            return;
        if (color_index & current_bits)
            return;
        current_bits |= color_index;
        comp_mask[i] = color_index;

        for (j = 0; (color_index & 1) == 0 && color_index != 0; j++)
            color_index >>= 1;
        comp_shift[i] = j;

        for (j = 0; color_index != 0; j++) {
            if ((color_index & 1) == 0)
                return;
            color_index >>= 1;
        }
        comp_bits[i] = j;


        for (j = 0; j < num_components; j++)
            colorants[j] = gx_max_color_value;
        colorants[i] = 0;
        color_index = dev_proc(dev, encode_color)(dev, colorants);
        if (color_index & comp_mask[i])
            return;
    }

    pinfo->separable_and_linear = GX_CINFO_SEP_LIN;
    for (i = 0; i < num_components; i++) {
        pinfo->comp_shift[i] = comp_shift[i];
        pinfo->comp_bits[i] = comp_bits[i];
        pinfo->comp_mask[i] = comp_mask[i];
    }


    for (i = 0; i < num_components; i++) {
        int dither = 1 << comp_bits[i];

        if (pinfo->dither_grays != 1 && dither == pinfo->dither_grays) {
            pinfo->gray_index = i;
            break;
        }
    }
}
