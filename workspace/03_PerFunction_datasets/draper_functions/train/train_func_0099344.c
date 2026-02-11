matroxfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			      unsigned blue, unsigned transp,
			      struct fb_info *fb_info)
{
	struct matrox_fb_info* minfo = container_of(fb_info, struct matrox_fb_info, fbcon);

	DBG(__func__)


	if (regno >= minfo->curr.cmap_len)
		return 1;

	if (minfo->fbcon.var.grayscale) {

		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	}

	red = CNVT_TOHW(red, minfo->fbcon.var.red.length);
	green = CNVT_TOHW(green, minfo->fbcon.var.green.length);
	blue = CNVT_TOHW(blue, minfo->fbcon.var.blue.length);
	transp = CNVT_TOHW(transp, minfo->fbcon.var.transp.length);

	switch (minfo->fbcon.var.bits_per_pixel) {
	case 4:
	case 8:
		mga_outb(M_DAC_REG, regno);
		mga_outb(M_DAC_VAL, red);
		mga_outb(M_DAC_VAL, green);
		mga_outb(M_DAC_VAL, blue);
		break;
	case 16:
		if (regno >= 16)
			break;
		{
			u_int16_t col =
				(red << minfo->fbcon.var.red.offset)     |
				(green << minfo->fbcon.var.green.offset) |
				(blue << minfo->fbcon.var.blue.offset)   |
				(transp << minfo->fbcon.var.transp.offset);
			minfo->cmap[regno] = col | (col << 16);
		}
		break;
	case 24:
	case 32:
		if (regno >= 16)
			break;
		minfo->cmap[regno] =
			(red   << minfo->fbcon.var.red.offset)   |
			(green << minfo->fbcon.var.green.offset) |
			(blue  << minfo->fbcon.var.blue.offset)  |
			(transp << minfo->fbcon.var.transp.offset);
		break;
	}
	return 0;
}
