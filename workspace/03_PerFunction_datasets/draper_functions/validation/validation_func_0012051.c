rt9455_pwr_rdy_work_callback(struct work_struct *work)
{
	struct rt9455_info *info = container_of(work, struct rt9455_info,
						pwr_rdy_work.work);
	struct device *dev = &info->client->dev;
	unsigned int pwr_rdy;
	int ret;

	ret = regmap_field_read(info->regmap_fields[F_PWR_RDY], &pwr_rdy);
	if (ret) {
		dev_err(dev, "Failed to read PWR_RDY bit\n");
		return;
	}
	switch (pwr_rdy) {
	case RT9455_PWR_FAULT:
		dev_dbg(dev, "Charger disconnected from power source\n");
		cancel_delayed_work_sync(&info->max_charging_time_work);
		break;
	case RT9455_PWR_GOOD:
		dev_dbg(dev, "Charger connected to power source\n");
		ret = regmap_field_write(info->regmap_fields[F_CHG_EN],
					 RT9455_CHARGE_ENABLE);
		if (ret) {
			dev_err(dev, "Failed to enable charging\n");
			return;
		}
		queue_delayed_work(system_power_efficient_wq,
				   &info->max_charging_time_work,
				   RT9455_MAX_CHARGING_TIME * HZ);
		break;
	}


	power_supply_changed(info->charger);
}
