bcma_chipco_watchdog_get_max_timer(struct bcma_drv_cc *cc)
{
	struct bcma_bus *bus = cc->core->bus;
	u32 nb;

	if (cc->capabilities & BCMA_CC_CAP_PMU) {
		if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706)
			nb = 32;
		else if (cc->core->id.rev < 26)
			nb = 16;
		else
			nb = (cc->core->id.rev >= 37) ? 32 : 24;
	} else {
		nb = 28;
	}
	if (nb == 32)
		return 0xffffffff;
	else
		return (1 << nb) - 1;
}
