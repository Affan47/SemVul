init_phys_status_page(struct intel_engine_cs *ring)
{
	struct drm_i915_private *dev_priv = ring->dev->dev_private;

	if (!dev_priv->status_page_dmah) {
		dev_priv->status_page_dmah =
			drm_pci_alloc(ring->dev, PAGE_SIZE, PAGE_SIZE);
		if (!dev_priv->status_page_dmah)
			return -ENOMEM;
	}

	ring->status_page.page_addr = dev_priv->status_page_dmah->vaddr;
	memset(ring->status_page.page_addr, 0, PAGE_SIZE);

	return 0;
}
