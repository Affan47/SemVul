dst_pio_enable(struct dst_state *state)
{
	if (dst_gpio_outb(state, ~0, RDC_8820_PIO_0_ENABLE, 0, NO_DELAY) < 0) {
		dprintk(verbose, DST_ERROR, 1, "dst_gpio_outb ERROR !");
		return -1;
	}
	udelay(1000);

	return 0;
}
