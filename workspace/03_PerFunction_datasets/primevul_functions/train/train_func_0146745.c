static void intel_iommu_init_qi(struct intel_iommu *iommu)
{


	if (!iommu->qi) {


		dmar_fault(-1, iommu);


		dmar_disable_qi(iommu);
	}

	if (dmar_enable_qi(iommu)) {


		iommu->flush.flush_context = __iommu_flush_context;
		iommu->flush.flush_iotlb = __iommu_flush_iotlb;
		pr_info("%s: Using Register based invalidation\n",
			iommu->name);
	} else {
		iommu->flush.flush_context = qi_flush_context;
		iommu->flush.flush_iotlb = qi_flush_iotlb;
		pr_info("%s: Using Queued invalidation\n", iommu->name);
	}
}
