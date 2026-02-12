(*get_encode_color(gx_device *dev))(gx_device *, const gx_color_value *)
{
    dev_proc_encode_color(*encode_proc);


    if ((encode_proc = dev_proc(dev, encode_color)) == 0) {
        if (dev->color_info.num_components == 1                          &&
            dev_proc(dev, map_rgb_color) != 0) {
            set_cinfo_polarity(dev, GX_CINFO_POLARITY_ADDITIVE);
            encode_proc = gx_backwards_compatible_gray_encode;
        } else  if ( (dev->color_info.num_components == 3    )           &&
             (encode_proc = dev_proc(dev, map_rgb_color)) != 0  )
            set_cinfo_polarity(dev, GX_CINFO_POLARITY_ADDITIVE);
        else if ( dev->color_info.num_components == 4                    &&
                 (encode_proc = dev_proc(dev, map_cmyk_color)) != 0   )
            set_cinfo_polarity(dev, GX_CINFO_POLARITY_SUBTRACTIVE);
    }


    if (encode_proc == 0) {
        if (dev->color_info.num_components == 1 && dev->color_info.depth != 0) {
            set_cinfo_polarity(dev, GX_CINFO_POLARITY_ADDITIVE);
            if (dev->color_info.max_gray == (1 << dev->color_info.depth) - 1)
                encode_proc = gx_default_gray_fast_encode;
            else
                encode_proc = gx_default_gray_encode;
            dev->color_info.separable_and_linear = GX_CINFO_SEP_LIN;
        } else if (colors_are_separable_and_linear(&dev->color_info)) {
            gx_color_value  max_gray = dev->color_info.max_gray;
            gx_color_value  max_color = dev->color_info.max_color;

            if ( (max_gray & (max_gray + 1)) == 0  &&
                 (max_color & (max_color + 1)) == 0  )

                encode_proc = gx_default_encode_color;
            else
                encode_proc = gx_default_encode_color;
        }
    }

    return encode_proc;
}
