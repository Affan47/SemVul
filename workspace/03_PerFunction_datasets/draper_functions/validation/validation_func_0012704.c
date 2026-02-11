arkfb_blank(int blank_mode, struct fb_info *info)
{
	struct arkfb_info *par = info->par;

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		fb_dbg(info, "unblank\n");
		svga_wseq_mask(par->state.vgabase, 0x01, 0x00, 0x20);
		svga_wcrt_mask(par->state.vgabase, 0x17, 0x80, 0x80);
		break;
	case FB_BLANK_NORMAL:
		fb_dbg(info, "blank\n");
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		svga_wcrt_mask(par->state.vgabase, 0x17, 0x80, 0x80);
		break;
	case FB_BLANK_POWERDOWN:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_VSYNC_SUSPEND:
		fb_dbg(info, "sync down\n");
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		svga_wcrt_mask(par->state.vgabase, 0x17, 0x00, 0x80);
		break;
	}
	return 0;
}
