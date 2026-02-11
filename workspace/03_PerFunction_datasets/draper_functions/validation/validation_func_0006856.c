lx_save_regs(struct lxfb_par *par)
{
	uint32_t filt;
	int i;


	do {
		i = read_gp(par, GP_BLT_STATUS);
	} while ((i & GP_BLT_STATUS_PB) || !(i & GP_BLT_STATUS_CE));


	rdmsrl(MSR_LX_MSR_PADSEL, par->msr.padsel);
	rdmsrl(MSR_GLCP_DOTPLL, par->msr.dotpll);
	rdmsrl(MSR_LX_GLD_MSR_CONFIG, par->msr.dfglcfg);
	rdmsrl(MSR_LX_SPARE_MSR, par->msr.dcspare);

	write_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);


	memcpy(par->gp, par->gp_regs, sizeof(par->gp));
	memcpy(par->dc, par->dc_regs, sizeof(par->dc));
	memcpy(par->vp, par->vp_regs, sizeof(par->vp));
	memcpy(par->fp, par->vp_regs + VP_FP_START, sizeof(par->fp));


	write_dc(par, DC_PAL_ADDRESS, 0);
	for (i = 0; i < ARRAY_SIZE(par->dc_pal); i++)
		par->dc_pal[i] = read_dc(par, DC_PAL_DATA);


	write_vp(par, VP_PAR, 0);
	for (i = 0; i < ARRAY_SIZE(par->vp_pal); i++)
		par->vp_pal[i] = read_vp(par, VP_PDR);


	filt = par->dc[DC_IRQ_FILT_CTL] | DC_IRQ_FILT_CTL_H_FILT_SEL;
	for (i = 0; i < ARRAY_SIZE(par->hcoeff); i += 2) {
		write_dc(par, DC_IRQ_FILT_CTL, (filt & 0xffffff00) | i);
		par->hcoeff[i] = read_dc(par, DC_FILT_COEFF1);
		par->hcoeff[i + 1] = read_dc(par, DC_FILT_COEFF2);
	}


	filt &= ~DC_IRQ_FILT_CTL_H_FILT_SEL;
	for (i = 0; i < ARRAY_SIZE(par->vcoeff); i++) {
		write_dc(par, DC_IRQ_FILT_CTL, (filt & 0xffffff00) | i);
		par->vcoeff[i] = read_dc(par, DC_FILT_COEFF1);
	}


	memcpy(par->vp_coeff, par->vp_regs + VP_VCR, sizeof(par->vp_coeff));
}
