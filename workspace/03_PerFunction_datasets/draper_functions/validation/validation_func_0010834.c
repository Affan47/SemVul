tricn_write(adapter_t *adapter, int bundle_addr, int module_addr,
		       int ch_addr, int reg_offset, u32 wr_data)
{
	int busy, attempts = TRICN_CMD_ATTEMPTS;

	writel(V_WRITE_DATA(wr_data) |
	       V_REGISTER_OFFSET(reg_offset) |
	       V_CHANNEL_ADDR(ch_addr) | V_MODULE_ADDR(module_addr) |
	       V_BUNDLE_ADDR(bundle_addr) |
	       V_SPI4_COMMAND(TRICN_CMD_WRITE),
	       adapter->regs + A_ESPI_CMD_ADDR);
	writel(0, adapter->regs + A_ESPI_GOSTAT);

	do {
		busy = readl(adapter->regs + A_ESPI_GOSTAT) & F_ESPI_CMD_BUSY;
	} while (busy && --attempts);

	if (busy)
		pr_err("%s: TRICN write timed out\n", adapter->name);

	return busy;
}
