pm2fb_fillrect(struct fb_info *info,
				const struct fb_fillrect *region)
{
	struct pm2fb_par *par = info->par;
	struct fb_fillrect modded;
	int vxres, vyres;
	u32 color = (info->fix.visual == FB_VISUAL_TRUECOLOR) ?
		((u32 *)info->pseudo_palette)[region->color] : region->color;

	if (info->state != FBINFO_STATE_RUNNING)
		return;
	if ((info->flags & FBINFO_HWACCEL_DISABLED) ||
		region->rop != ROP_COPY ) {
		cfb_fillrect(info, region);
		return;
	}

	vxres = info->var.xres_virtual;
	vyres = info->var.yres_virtual;

	memcpy(&modded, region, sizeof(struct fb_fillrect));

	if (!modded.width || !modded.height ||
	    modded.dx >= vxres || modded.dy >= vyres)
		return;

	if (modded.dx + modded.width  > vxres)
		modded.width  = vxres - modded.dx;
	if (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	if (info->var.bits_per_pixel == 8)
		color |= color << 8;
	if (info->var.bits_per_pixel <= 16)
		color |= color << 16;

	WAIT_FIFO(par, 3);
	pm2_WR(par, PM2R_CONFIG, PM2F_CONFIG_FB_WRITE_ENABLE);
	pm2_WR(par, PM2R_RECTANGLE_ORIGIN, (modded.dy << 16) | modded.dx);
	pm2_WR(par, PM2R_RECTANGLE_SIZE, (modded.height << 16) | modded.width);
	if (info->var.bits_per_pixel != 24) {
		WAIT_FIFO(par, 2);
		pm2_WR(par, PM2R_FB_BLOCK_COLOR, color);
		wmb();
		pm2_WR(par, PM2R_RENDER,
				PM2F_RENDER_RECTANGLE | PM2F_RENDER_FASTFILL);
	} else {
		WAIT_FIFO(par, 4);
		pm2_WR(par, PM2R_COLOR_DDA_MODE, 1);
		pm2_WR(par, PM2R_CONSTANT_COLOR, color);
		wmb();
		pm2_WR(par, PM2R_RENDER,
				PM2F_RENDER_RECTANGLE |
				PM2F_INCREASE_X | PM2F_INCREASE_Y );
		pm2_WR(par, PM2R_COLOR_DDA_MODE, 0);
	}
}
