ov2640_reset(struct i2c_client *client)
{
	int ret;
	const struct regval_list reset_seq[] = {
		{BANK_SEL, BANK_SEL_SENS},
		{COM7, COM7_SRST},
		ENDMARKER,
	};

	ret = ov2640_write_array(client, reset_seq);
	if (ret)
		goto err;

	msleep(5);
err:
	dev_dbg(&client->dev, "%s: (ret %d)", __func__, ret);
	return ret;
}
