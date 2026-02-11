amd_iommu_erratum_746_workaround(struct amd_iommu *iommu)
{
	u32 value;

	if ((boot_cpu_data.x86 != 0x15) ||
	    (boot_cpu_data.x86_model < 0x10) ||
	    (boot_cpu_data.x86_model > 0x1f))
		return;

	pci_write_config_dword(iommu->dev, 0xf0, 0x90);
	pci_read_config_dword(iommu->dev, 0xf4, &value);

	if (value & BIT(2))
		return;


	pci_write_config_dword(iommu->dev, 0xf0, 0x90 | (1 << 8));

	pci_write_config_dword(iommu->dev, 0xf4, value | 0x4);
	pr_info("AMD-Vi: Applying erratum 746 workaround for IOMMU at %s\n",
		dev_name(&iommu->dev->dev));


	pci_write_config_dword(iommu->dev, 0xf0, 0x90);
}
