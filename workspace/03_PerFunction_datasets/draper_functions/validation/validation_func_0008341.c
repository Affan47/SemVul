vp_interrupt(int irq, void *opaque)
{
	struct virtio_pci_device *vp_dev = opaque;
	u8 isr;


	isr = ioread8(vp_dev->isr);


	if (!isr)
		return IRQ_NONE;


	if (isr & VIRTIO_PCI_ISR_CONFIG)
		vp_config_changed(irq, opaque);

	return vp_vring_interrupt(irq, opaque);
}
