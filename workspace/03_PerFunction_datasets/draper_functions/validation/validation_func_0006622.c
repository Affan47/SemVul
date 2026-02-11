tmiofb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *info)
{
	struct tmiofb_par *par = info->par;

	if (regno < ARRAY_SIZE(par->pseudo_palette)) {
		par->pseudo_palette[regno] =
			((red & 0xf800)) |
			((green & 0xfc00) >>  5) |
			((blue & 0xf800) >> 11);
		return 0;
	}

	return -EINVAL;
}
