static void setup_struct_wldev_for_init(struct b43_wldev *dev)
{
	dev->dfq_valid = false;


	dev->radio_hw_enable = true;


	memset(&dev->stats, 0, sizeof(dev->stats));

	setup_struct_phy_for_init(dev, &dev->phy);


	dev->irq_reason = 0;
	memset(dev->dma_reason, 0, sizeof(dev->dma_reason));
	dev->irq_mask = B43_IRQ_MASKTEMPLATE;
	if (b43_modparam_verbose < B43_VERBOSITY_DEBUG)
		dev->irq_mask &= ~B43_IRQ_PHY_TXERR;

	dev->mac_suspended = 1;


	memset(&dev->noisecalc, 0, sizeof(dev->noisecalc));
}
