static struct dmar_domain *find_domain(struct device *dev)
{
	struct device_domain_info *info;


	info = dev->archdata.iommu;
	if (likely(info))
		return info->domain;
	return NULL;
}
