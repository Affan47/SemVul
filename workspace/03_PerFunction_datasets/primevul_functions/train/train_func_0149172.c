static int iommu_no_mapping(struct device *dev)
{
	int found;

	if (iommu_dummy(dev))
		return 1;

	if (!iommu_identity_mapping)
		return 0;

	found = identity_mapping(dev);
	if (found) {
		if (iommu_should_identity_map(dev, 0))
			return 1;
		else {


			dmar_remove_one_dev_info(dev);
			dev_info(dev, "32bit DMA uses non-identity mapping\n");
			return 0;
		}
	} else {


		if (iommu_should_identity_map(dev, 0)) {
			int ret;
			ret = domain_add_dev_info(si_domain, dev);
			if (!ret) {
				dev_info(dev, "64bit DMA uses identity mapping\n");
				return 1;
			}
		}
	}

	return 0;
}
