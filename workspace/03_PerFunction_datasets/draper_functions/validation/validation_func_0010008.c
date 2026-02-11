console_store(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	struct atm_dev *atmdev = container_of(dev, struct atm_dev, class_dev);
	struct solos_card *card = atmdev->dev_data;
	int err;

	err = send_command(card, SOLOS_CHAN(atmdev), buf, count);

	return err?:count;
}
