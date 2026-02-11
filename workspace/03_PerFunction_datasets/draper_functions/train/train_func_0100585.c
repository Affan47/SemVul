hym8563_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct hym8563 *hym8563 = i2c_get_clientdata(client);
	u8 buf[7];
	int ret;


	if (tm->tm_year < 100 || tm->tm_year >= 200)
		return -EINVAL;

	buf[0] = bin2bcd(tm->tm_sec);
	buf[1] = bin2bcd(tm->tm_min);
	buf[2] = bin2bcd(tm->tm_hour);
	buf[3] = bin2bcd(tm->tm_mday);
	buf[4] = bin2bcd(tm->tm_wday);
	buf[5] = bin2bcd(tm->tm_mon + 1);


	buf[6] = bin2bcd(tm->tm_year - 100);


	ret = i2c_smbus_write_byte_data(client, HYM8563_CTL1,
						HYM8563_CTL1_STOP);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_i2c_block_data(client, HYM8563_SEC, 7, buf);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(client, HYM8563_CTL1, 0);
	if (ret < 0)
		return ret;

	hym8563->valid = true;

	return 0;
}
