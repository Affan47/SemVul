brcms_b_clkctl_clk(struct brcms_hardware *wlc_hw, enum bcma_clkmode mode)
{
	if (ai_get_cccaps(wlc_hw->sih) & CC_CAP_PMU) {


		if (wlc_hw->clk) {
			if (mode == BCMA_CLKMODE_FAST) {
				bcma_set32(wlc_hw->d11core,
					   D11REGOFFS(clk_ctl_st),
					   CCS_FORCEHT);

				udelay(64);

				SPINWAIT(
				    ((bcma_read32(wlc_hw->d11core,
				      D11REGOFFS(clk_ctl_st)) &
				      CCS_HTAVAIL) == 0),
				      PMU_MAX_TRANSITION_DLY);
				WARN_ON(!(bcma_read32(wlc_hw->d11core,
					D11REGOFFS(clk_ctl_st)) &
					CCS_HTAVAIL));
			} else {
				if ((ai_get_pmurev(wlc_hw->sih) == 0) &&
				    (bcma_read32(wlc_hw->d11core,
					D11REGOFFS(clk_ctl_st)) &
					(CCS_FORCEHT | CCS_HTAREQ)))
					SPINWAIT(
					    ((bcma_read32(wlc_hw->d11core,
					      offsetof(struct d11regs,
						       clk_ctl_st)) &
					      CCS_HTAVAIL) == 0),
					      PMU_MAX_TRANSITION_DLY);
				bcma_mask32(wlc_hw->d11core,
					D11REGOFFS(clk_ctl_st),
					~CCS_FORCEHT);
			}
		}
		wlc_hw->forcefastclk = (mode == BCMA_CLKMODE_FAST);
	} else {


		wlc_hw->forcefastclk = ai_clkctl_cc(wlc_hw->sih, mode);


		if (wlc_hw->forcefastclk && wlc_hw->clk)
			WARN_ON(!(bcma_aread32(wlc_hw->d11core, BCMA_IOST) &
				  SISF_FCLKA));


		if (wlc_hw->forcefastclk)
			mboolset(wlc_hw->wake_override,
				 BRCMS_WAKE_OVERRIDE_FORCEFAST);
		else
			mboolclr(wlc_hw->wake_override,
				 BRCMS_WAKE_OVERRIDE_FORCEFAST);
	}
}
