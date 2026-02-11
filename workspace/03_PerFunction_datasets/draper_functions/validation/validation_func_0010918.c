auok190x_issue_pixels(struct auok190xfb_par *par, int size,
				 u16 *data)
{
	struct fb_info *info = par->info;
	struct device *dev = par->info->device;

	if (info->var.bits_per_pixel == 8 && info->var.grayscale)
		auok190x_issue_pixels_gray8(par, size, data);
	else if (info->var.bits_per_pixel == 16)
		auok190x_issue_pixels_rgb565(par, size, data);
	else
		dev_err(dev, "unsupported color mode (bits: %d, gray: %d)\n",
			info->var.bits_per_pixel, info->var.grayscale);

	return 0;
}
