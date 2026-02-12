static void sm7xx_resolution_probe(struct smtcfb_info *sfb)
{

	if (smtc_scr_info.lfb_width != 0) {
		sfb->fb->var.xres = smtc_scr_info.lfb_width;
		sfb->fb->var.yres = smtc_scr_info.lfb_height;
		sfb->fb->var.bits_per_pixel = smtc_scr_info.lfb_depth;
		goto final;
	}


	sfb->fb->var.xres = SCREEN_X_RES;
	sfb->fb->var.yres = SCREEN_Y_RES_PC;
	sfb->fb->var.bits_per_pixel = SCREEN_BPP;

#ifdef CONFIG_MIPS


	sfb->fb->var.yres = SCREEN_Y_RES_NETBOOK;
#endif

final:
	big_pixel_depth(sfb->fb->var.bits_per_pixel, smtc_scr_info.lfb_depth);
}
