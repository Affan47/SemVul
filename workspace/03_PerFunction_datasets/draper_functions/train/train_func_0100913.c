ahci_stop_fis_rx(struct ata_port *ap)
{
	void __iomem *port_mmio = ahci_port_base(ap);
	u32 tmp;


	tmp = readl(port_mmio + PORT_CMD);
	tmp &= ~PORT_CMD_FIS_RX;
	writel(tmp, port_mmio + PORT_CMD);


	tmp = ata_wait_register(ap, port_mmio + PORT_CMD, PORT_CMD_FIS_ON,
				PORT_CMD_FIS_ON, 10, 1000);
	if (tmp & PORT_CMD_FIS_ON)
		return -EBUSY;

	return 0;
}
