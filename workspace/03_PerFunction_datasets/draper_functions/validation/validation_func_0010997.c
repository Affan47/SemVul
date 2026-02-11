da9150_reg_read(struct da9150 *da9150, u16 reg)
{
	int val, ret;

	ret = regmap_read(da9150->regmap, reg, &val);
	if (ret)
		dev_err(da9150->dev, "Failed to read from reg 0x%x: %d\n",
			reg, ret);

	return (u8) val;
}
