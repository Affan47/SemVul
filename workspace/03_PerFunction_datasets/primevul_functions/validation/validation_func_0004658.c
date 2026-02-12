void destroy_iommu_domain(struct iommu_domain *domain)
{

	(void)memset(domain, 0U, sizeof(*domain));
}
