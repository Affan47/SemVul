sis_driver_load(struct drm_device *dev, unsigned long chipset)
{
	drm_sis_private_t *dev_priv;

	pci_set_master(dev->pdev);

	dev_priv = kzalloc(sizeof(drm_sis_private_t), GFP_KERNEL);
	if (dev_priv == NULL)
		return -ENOMEM;

	idr_init(&dev_priv->object_idr);
	dev->dev_private = (void *)dev_priv;
	dev_priv->chipset = chipset;

	return 0;
}
