radeon_pm_enable_dll_m10(struct radeonfb_info *rinfo)
{
	u32 dll_value;
	u32 dll_sleep_mask = 0;
	u32 dll_reset_mask = 0;
	u32 mc;

#define DLL_RESET_DELAY 	5
#define DLL_SLEEP_DELAY		1

	OUTMC(rinfo, ixR300_MC_DLL_CNTL, rinfo->save_regs[70]);
	mc = INREG(MC_CNTL);

	switch (mc & 0x3) {
	case 1:
		if (mc & 0x4)
			break;
	case 2:
		dll_sleep_mask |= MDLL_R300_RDCK__MRDCKB_SLEEP;
		dll_reset_mask |= MDLL_R300_RDCK__MRDCKB_RESET;
	case 0:
		dll_sleep_mask |= MDLL_R300_RDCK__MRDCKA_SLEEP;
		dll_reset_mask |= MDLL_R300_RDCK__MRDCKA_RESET;
	}
	switch (mc & 0x3) {
	case 1:
		if (!(mc & 0x4))
			break;
	case 2:
		dll_sleep_mask |= MDLL_R300_RDCK__MRDCKD_SLEEP;
		dll_reset_mask |= MDLL_R300_RDCK__MRDCKD_RESET;
		dll_sleep_mask |= MDLL_R300_RDCK__MRDCKC_SLEEP;
		dll_reset_mask |= MDLL_R300_RDCK__MRDCKC_RESET;
	}

	dll_value = INPLL(pllMDLL_RDCKA);


	dll_value &= ~(dll_sleep_mask);
	OUTPLL(pllMDLL_RDCKA, dll_value);
	mdelay( DLL_SLEEP_DELAY);

	dll_value &= ~(dll_reset_mask);
	OUTPLL(pllMDLL_RDCKA, dll_value);
	mdelay( DLL_RESET_DELAY);

#undef DLL_RESET_DELAY
#undef DLL_SLEEP_DELAY
}
