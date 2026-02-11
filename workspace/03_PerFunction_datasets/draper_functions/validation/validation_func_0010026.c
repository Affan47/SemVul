pci_create_capabilities_sysfs(struct pci_dev *dev)
{
	int retval;
	struct bin_attribute *attr;


	if (dev->vpd) {
		attr = kzalloc(sizeof(*attr), GFP_ATOMIC);
		if (!attr)
			return -ENOMEM;

		sysfs_bin_attr_init(attr);
		attr->size = dev->vpd->len;
		attr->attr.name = "vpd";
		attr->attr.mode = S_IRUSR | S_IWUSR;
		attr->read = read_vpd_attr;
		attr->write = write_vpd_attr;
		retval = sysfs_create_bin_file(&dev->dev.kobj, attr);
		if (retval) {
			kfree(attr);
			return retval;
		}
		dev->vpd->attr = attr;
	}


	pcie_aspm_create_sysfs_dev_files(dev);

	if (!pci_probe_reset_function(dev)) {
		retval = device_create_file(&dev->dev, &reset_attr);
		if (retval)
			goto error;
		dev->reset_fn = 1;
	}
	return 0;

error:
	pcie_aspm_remove_sysfs_dev_files(dev);
	if (dev->vpd && dev->vpd->attr) {
		sysfs_remove_bin_file(&dev->dev.kobj, dev->vpd->attr);
		kfree(dev->vpd->attr);
	}

	return retval;
}
