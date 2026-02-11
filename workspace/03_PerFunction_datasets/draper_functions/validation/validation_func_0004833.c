lx_dsp_reg_readbuf(struct lx6464es *chip, int port, u32 *data,
			       u32 len)
{
	u32 __iomem *address = lx_dsp_register(chip, port);
	int i;


	for (i = 0; i != len; ++i)
		data[i] = ioread32(address + i);
}
