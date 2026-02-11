tc3589x_reg_read(struct tc3589x *tc3589x, u8 reg)
{
	int ret;

	ret = i2c_smbus_read_byte_data(tc3589x->i2c, reg);
	if (ret < 0)
		dev_err(tc3589x->dev, "failed to read reg %#x: %d\n",
			reg, ret);

	return ret;
}
