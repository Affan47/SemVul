bq27xxx_battery_read_soc(struct bq27xxx_device_info *di)
{
	int soc;

	soc = bq27xxx_read(di, BQ27XXX_REG_SOC, false);

	if (soc < 0)
		dev_dbg(di->dev, "error reading State-of-Charge\n");

	return soc;
}
