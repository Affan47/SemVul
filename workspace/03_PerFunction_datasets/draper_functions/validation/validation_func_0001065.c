ov9640_reg_rmw(struct i2c_client *client, u8 reg, u8 set, u8 unset)
{
	u8 val;
	int ret;

	ret = ov9640_reg_read(client, reg, &val);
	if (ret) {
		dev_err(&client->dev,
			"[Read]-Modify-Write of register %02x failed!\n", reg);
		return val;
	}

	val |= set;
	val &= ~unset;

	ret = ov9640_reg_write(client, reg, val);
	if (ret)
		dev_err(&client->dev,
			"Read-Modify-[Write] of register %02x failed!\n", reg);

	return ret;
}
