drm_ati_alloc_pcigart_table(struct drm_device *dev,
				       struct drm_ati_pcigart_info *gart_info)
{
	gart_info->table_handle = drm_pci_alloc(dev, gart_info->table_size,
						PAGE_SIZE);
	if (gart_info->table_handle == NULL)
		return -ENOMEM;

	return 0;
}
