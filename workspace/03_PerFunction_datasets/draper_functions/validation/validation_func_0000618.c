saa7134_go7007_write_interrupt(struct go7007 *go, int addr, int data)
{
	struct saa7134_go7007 *saa = go->hpi_context;
	struct saa7134_dev *dev = saa->dev;
	int i;
	u16 status_reg;

#ifdef GO7007_HPI_DEBUG
	pr_debug("saa7134-go7007: WriteInterrupt: %04x %04x\n", addr, data);
#endif

	for (i = 0; i < 100; ++i) {
		gpio_read(dev, HPI_ADDR_INTR_STATUS, &status_reg);
		if (!(status_reg & 0x0010))
			break;
		msleep(10);
	}
	if (i == 100) {
		pr_err("saa7134-go7007: device is hung, status reg = 0x%04x\n",
			status_reg);
		return -1;
	}
	gpio_write(dev, HPI_ADDR_INTR_WR_PARAM, data);
	gpio_write(dev, HPI_ADDR_INTR_WR_INDEX, addr);

	return 0;
}
