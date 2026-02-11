ahci_port_init(struct device *dev, struct ata_port *ap,
			   int port_no, void __iomem *mmio,
			   void __iomem *port_mmio)
{
	struct ahci_host_priv *hpriv = ap->host->private_data;
	const char *emsg = NULL;
	int rc;
	u32 tmp;


	rc = ahci_deinit_port(ap, &emsg);
	if (rc)
		dev_warn(dev, "%s (%d)\n", emsg, rc);


	tmp = readl(port_mmio + PORT_SCR_ERR);
	VPRINTK("PORT_SCR_ERR 0x%x\n", tmp);
	writel(tmp, port_mmio + PORT_SCR_ERR);


	tmp = readl(port_mmio + PORT_IRQ_STAT);
	VPRINTK("PORT_IRQ_STAT 0x%x\n", tmp);
	if (tmp)
		writel(tmp, port_mmio + PORT_IRQ_STAT);

	writel(1 << port_no, mmio + HOST_IRQ_STAT);


	tmp = readl(port_mmio + PORT_CMD);
	if ((tmp & PORT_CMD_ESP) && (hpriv->cap & HOST_CAP_SXS))
		ap->pflags |= ATA_PFLAG_EXTERNAL;
}
