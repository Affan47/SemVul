__xen_pcibk_release_pci_dev(struct xen_pcibk_device *pdev,
					struct pci_dev *dev, bool lock)
{
	struct passthrough_dev_data *dev_data = pdev->pci_dev_data;
	struct pci_dev_entry *dev_entry, *t;
	struct pci_dev *found_dev = NULL;

	mutex_lock(&dev_data->lock);

	list_for_each_entry_safe(dev_entry, t, &dev_data->dev_list, list) {
		if (dev_entry->dev == dev) {
			list_del(&dev_entry->list);
			found_dev = dev_entry->dev;
			kfree(dev_entry);
		}
	}

	mutex_unlock(&dev_data->lock);

	if (found_dev) {
		if (lock)
			device_lock(&found_dev->dev);
		pcistub_put_pci_dev(found_dev);
		if (lock)
			device_unlock(&found_dev->dev);
	}
}
