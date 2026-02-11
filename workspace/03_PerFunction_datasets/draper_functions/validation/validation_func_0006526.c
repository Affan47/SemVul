cyberpro_alloc_fb_info(unsigned int id, char *name)
{
	struct cfb_info *cfb;

	cfb = kzalloc(sizeof(struct cfb_info), GFP_KERNEL);
	if (!cfb)
		return NULL;


	cfb->id			= id;

	if (id == ID_CYBERPRO_5000)
		cfb->ref_ps	= 40690;
	else
		cfb->ref_ps	= 69842;

	cfb->divisors[0]	= 1;
	cfb->divisors[1]	= 2;
	cfb->divisors[2]	= 4;

	if (id == ID_CYBERPRO_2000)
		cfb->divisors[3] = 8;
	else
		cfb->divisors[3] = 6;

	strcpy(cfb->fb.fix.id, name);

	cfb->fb.fix.type	= FB_TYPE_PACKED_PIXELS;
	cfb->fb.fix.type_aux	= 0;
	cfb->fb.fix.xpanstep	= 0;
	cfb->fb.fix.ypanstep	= 1;
	cfb->fb.fix.ywrapstep	= 0;

	switch (id) {
	case ID_IGA_1682:
		cfb->fb.fix.accel = 0;
		break;

	case ID_CYBERPRO_2000:
		cfb->fb.fix.accel = FB_ACCEL_IGS_CYBER2000;
		break;

	case ID_CYBERPRO_2010:
		cfb->fb.fix.accel = FB_ACCEL_IGS_CYBER2010;
		break;

	case ID_CYBERPRO_5000:
		cfb->fb.fix.accel = FB_ACCEL_IGS_CYBER5000;
		break;
	}

	cfb->fb.var.nonstd	= 0;
	cfb->fb.var.activate	= FB_ACTIVATE_NOW;
	cfb->fb.var.height	= -1;
	cfb->fb.var.width	= -1;
	cfb->fb.var.accel_flags	= FB_ACCELF_TEXT;

	cfb->fb.fbops		= &cyber2000fb_ops;
	cfb->fb.flags		= FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	cfb->fb.pseudo_palette	= cfb->pseudo_palette;

	spin_lock_init(&cfb->reg_b0_lock);

	fb_alloc_cmap(&cfb->fb.cmap, NR_PALETTE, 0);

	return cfb;
}
