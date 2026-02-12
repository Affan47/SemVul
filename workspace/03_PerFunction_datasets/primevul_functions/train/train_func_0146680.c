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


			dmar_remove_one_dev_info(si_domain, dev);
			pr_info("32bit %s uses non-identity mapping\n",
				dev_name(dev));
			return 0;
		}
	} else {


		if (iommu_should_identity_map(dev, 0)) {
			int ret;
			ret = domain_add_dev_info(si_domain, dev);
			if (!ret) {
				pr_info("64bit %s uses identity mapping\n",
					dev_name(dev));
				return 1;
			}
		}
	}

	return 0;
}
