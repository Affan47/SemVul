mac_var_to_vmode(const struct fb_var_screeninfo *var, int *vmode,
		     int *cmode)
{
    const struct mode_map *map;

    if (var->bits_per_pixel <= 8)
	*cmode = CMODE_8;
    else if (var->bits_per_pixel <= 16)
	*cmode = CMODE_16;
    else if (var->bits_per_pixel <= 32)
	*cmode = CMODE_32;
    else
	return -EINVAL;


    for (map = mac_modes; map->vmode != -1; map++) {
	const struct fb_videomode *mode = map->mode;

	if (var->xres > mode->xres || var->yres > mode->yres)
	    continue;
	if (var->xres_virtual > mode->xres || var->yres_virtual > mode->yres)
	    continue;
	if (var->pixclock > mode->pixclock)
	    continue;
	if ((var->vmode & FB_VMODE_MASK) != mode->vmode)
	    continue;
	*vmode = map->vmode;


	map++;
	while (map->vmode != -1) {
	    const struct fb_videomode *clk_mode = map->mode;

	    if (mode->xres != clk_mode->xres || mode->yres != clk_mode->yres)
		break;
	    if (var->pixclock > mode->pixclock)
	        break;
	    if (mode->vmode != clk_mode->vmode)
		continue;
	    *vmode = map->vmode;
	    map++;
	}
	return 0;
    }
    return -EINVAL;
}
