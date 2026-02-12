static void quirk_iommu_g4x_gfx(struct pci_dev *dev)
{

	pci_info(dev, "Disabling IOMMU for graphics on this chipset\n");
	dmar_map_gfx = 0;
}
