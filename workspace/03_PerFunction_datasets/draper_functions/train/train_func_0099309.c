set_voltage_sel(struct regulator_dev *rdev, unsigned selector)
{
	const struct supply_info *info;
	struct tps6524x *hw;

	hw	= rdev_get_drvdata(rdev);
	info	= &supply_info[rdev_get_id(rdev)];

	if (rdev->desc->n_voltages == 1)
		return -EINVAL;

	return write_field(hw, &info->voltage, selector);
}
