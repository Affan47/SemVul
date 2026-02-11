bcma_core_pll_ctl(struct bcma_device *core, u32 req, u32 status, bool on)
{
	u16 i;

	WARN_ON(req & ~BCMA_CLKCTLST_EXTRESREQ);
	WARN_ON(status & ~BCMA_CLKCTLST_EXTRESST);

	if (on) {
		bcma_set32(core, BCMA_CLKCTLST, req);
		for (i = 0; i < 10000; i++) {
			if ((bcma_read32(core, BCMA_CLKCTLST) & status) ==
			    status) {
				i = 0;
				break;
			}
			udelay(10);
		}
		if (i)
			bcma_err(core->bus, "PLL enable timeout\n");
	} else {


		bcma_mask32(core, BCMA_CLKCTLST, ~req);
		bcma_read32(core, BCMA_CLKCTLST);
	}
}
