b43_dma_translation_in_low_word(struct b43_wldev *dev,
					    enum b43_dmatype type)
{
	if (type != B43_DMA_64BIT)
		return true;

#ifdef CONFIG_B43_SSB
	if (dev->dev->bus_type == B43_BUS_SSB &&
	    dev->dev->sdev->bus->bustype == SSB_BUSTYPE_PCI &&
	    !(pci_is_pcie(dev->dev->sdev->bus->host_pci) &&
	      ssb_read32(dev->dev->sdev, SSB_TMSHIGH) & SSB_TMSHIGH_DMA64))
			return true;
#endif
	return false;
}
