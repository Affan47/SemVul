get_component_status(struct device *cdev,
				    struct device_attribute *attr,char *buf)
{
	struct enclosure_device *edev = to_enclosure_device(cdev->parent);
	struct enclosure_component *ecomp = to_enclosure_component(cdev);

	if (edev->cb->get_status)
		edev->cb->get_status(edev, ecomp);
	return snprintf(buf, 40, "%s\n", enclosure_status[ecomp->status]);
}
