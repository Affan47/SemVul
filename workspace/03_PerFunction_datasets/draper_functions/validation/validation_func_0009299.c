tsi148_iack_received(struct tsi148_driver *bridge)
{
	u32 tmp;

	tmp = ioread32be(bridge->base + TSI148_LCSR_VICR);

	if (tmp & TSI148_LCSR_VICR_IRQS)
		return 0;
	else
		return 1;
}
