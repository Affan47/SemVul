nv_disable_hw_interrupts ( struct forcedeth_private *priv )
{
	void *ioaddr = priv->mmio_addr;

	writel ( 0, ioaddr + NvRegIrqMask );
	pci_push ( ioaddr );
}
