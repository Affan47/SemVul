rt9455_irq_handler_thread(int irq, void *data)
{
	struct rt9455_info *info = data;
	struct device *dev;
	bool alert_userspace = false;
	bool is_battery_absent = false;
	unsigned int status;
	int ret;

	if (!info)
		return IRQ_NONE;

	dev = &info->client->dev;

	if (irq != info->client->irq) {
		dev_err(dev, "Interrupt is not for RT9455 charger\n");
		return IRQ_NONE;
	}

	ret = regmap_field_read(info->regmap_fields[F_STAT], &status);
	if (ret) {
		dev_err(dev, "Failed to read STAT bits\n");
		return IRQ_HANDLED;
	}
	dev_dbg(dev, "Charger status is %d\n", status);


	ret = rt9455_irq_handler_check_irq1_register(info, &is_battery_absent,
						     &alert_userspace);
	if (ret) {
		dev_err(dev, "Failed to handle IRQ1 register\n");
		return IRQ_HANDLED;
	}

	ret = rt9455_irq_handler_check_irq2_register(info, is_battery_absent,
						     &alert_userspace);
	if (ret) {
		dev_err(dev, "Failed to handle IRQ2 register\n");
		return IRQ_HANDLED;
	}

	ret = rt9455_irq_handler_check_irq3_register(info, &alert_userspace);
	if (ret) {
		dev_err(dev, "Failed to handle IRQ3 register\n");
		return IRQ_HANDLED;
	}

	if (alert_userspace) {


		if (info->charger)
			power_supply_changed(info->charger);
	}

	return IRQ_HANDLED;
}
