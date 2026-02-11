rx8025_read_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct rx8025_data *rx8025 = dev_get_drvdata(dev);
	struct i2c_client *client = rx8025->client;
	u8 ald[2];
	int ctrl2, err;

	if (client->irq <= 0)
		return -EINVAL;

	err = rx8025_read_regs(client, RX8025_REG_ALDMIN, 2, ald);
	if (err)
		return err;

	ctrl2 = rx8025_read_reg(client, RX8025_REG_CTRL2);
	if (ctrl2 < 0)
		return ctrl2;

	dev_dbg(dev, "%s: read alarm 0x%02x 0x%02x ctrl2 %02x\n",
		__func__, ald[0], ald[1], ctrl2);


	t->time.tm_sec = 0;
	t->time.tm_min = bcd2bin(ald[0] & 0x7f);
	if (rx8025->ctrl1 & RX8025_BIT_CTRL1_1224)
		t->time.tm_hour = bcd2bin(ald[1] & 0x3f);
	else
		t->time.tm_hour = bcd2bin(ald[1] & 0x1f) % 12
			+ (ald[1] & 0x20 ? 12 : 0);

	t->time.tm_wday = -1;
	t->time.tm_mday = -1;
	t->time.tm_mon = -1;
	t->time.tm_year = -1;

	dev_dbg(dev, "%s: date: %ds %dm %dh %dmd %dm %dy\n",
		__func__,
		t->time.tm_sec, t->time.tm_min, t->time.tm_hour,
		t->time.tm_mday, t->time.tm_mon, t->time.tm_year);
	t->enabled = !!(rx8025->ctrl1 & RX8025_BIT_CTRL1_DALE);
	t->pending = (ctrl2 & RX8025_BIT_CTRL2_DAFG) && t->enabled;

	return err;
}
