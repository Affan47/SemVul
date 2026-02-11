mcp794xx_set_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ds1307 *ds1307 = i2c_get_clientdata(client);
	unsigned char *regs = ds1307->regs;
	int ret;

	if (!test_bit(HAS_ALARM, &ds1307->flags))
		return -EINVAL;

	dev_dbg(dev, "%s, sec=%d min=%d hour=%d wday=%d mday=%d mon=%d "
		"enabled=%d pending=%d\n", __func__,
		t->time.tm_sec, t->time.tm_min, t->time.tm_hour,
		t->time.tm_wday, t->time.tm_mday, t->time.tm_mon,
		t->enabled, t->pending);


	ret = ds1307->read_block_data(client, MCP794XX_REG_CONTROL, 10, regs);
	if (ret < 0)
		return ret;


	regs[3] = bin2bcd(t->time.tm_sec);
	regs[4] = bin2bcd(t->time.tm_min);
	regs[5] = bin2bcd(t->time.tm_hour);
	regs[6] = bin2bcd(t->time.tm_wday + 1);
	regs[7] = bin2bcd(t->time.tm_mday);
	regs[8] = bin2bcd(t->time.tm_mon + 1);


	regs[6] &= ~MCP794XX_BIT_ALMX_IF;

	regs[6] |= MCP794XX_MSK_ALMX_MATCH;

	regs[0] &= ~MCP794XX_BIT_ALM0_EN;

	ret = ds1307->write_block_data(client, MCP794XX_REG_CONTROL, 10, regs);
	if (ret < 0)
		return ret;

	if (!t->enabled)
		return 0;
	regs[0] |= MCP794XX_BIT_ALM0_EN;
	return i2c_smbus_write_byte_data(client, MCP794XX_REG_CONTROL, regs[0]);
}
