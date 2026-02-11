svg_get_color(gx_device_svg *svg, const gx_drawing_color *pdc)
{

    gx_color_index color = gx_no_color_index;

    if (gx_dc_is_pure(pdc))
	color = gx_dc_pure_color(pdc);
    return color;
}
