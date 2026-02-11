sm501fb_setup_gamma(struct sm501fb_info *fbi,
				unsigned long palette)
{
	unsigned long value = 0;
	int offset;


	for (offset = 0; offset < 256 * 4; offset += 4) {
		smc501_writel(value, fbi->regs + palette + offset);
		value += 0x010101;
	}
}
