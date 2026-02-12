static struct dmar_drhd_rt *device_to_dmaru(uint8_t bus, uint8_t devfun)
{
	struct dmar_drhd_rt *dmaru = NULL;
	uint16_t bdf = ((uint16_t)bus << 8U) | devfun;
	uint32_t index = pci_lookup_drhd_for_pbdf(bdf);

	if (index == INVALID_DRHD_INDEX) {
		pr_fatal("BDF %02x:%02x:%x has no IOMMU\n", bus, devfun >> 3U, devfun & 7U);


	} else {
		dmaru = &dmar_drhd_units[index];
	}

	return dmaru;
}
