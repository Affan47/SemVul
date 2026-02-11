max77802_set_ramp_delay_2bit(struct regulator_dev *rdev,
					int ramp_delay)
{
	int id = rdev_get_id(rdev);
	unsigned int ramp_value;

	if (id > MAX77802_BUCK4) {
			dev_warn(&rdev->dev,
				 "%s: regulator: ramp delay not supported\n",
				 rdev->desc->name);
		return -EINVAL;
	}
	ramp_value = max77802_find_ramp_value(rdev, ramp_table_77802_2bit,
				ARRAY_SIZE(ramp_table_77802_2bit), ramp_delay);

	return regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  MAX77802_RAMP_RATE_MASK_2BIT,
				  ramp_value << MAX77802_RAMP_RATE_SHIFT_2BIT);
}
