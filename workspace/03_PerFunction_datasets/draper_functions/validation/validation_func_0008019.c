store_master_fader(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t len, int nr)
{
	struct lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	struct lp55xx_chip *chip = led->chip;
	int ret;
	unsigned long val;

	if (kstrtoul(buf, 0, &val))
		return -EINVAL;

	if (val > 0xff)
		return -EINVAL;

	mutex_lock(&chip->lock);
	ret = lp55xx_write(chip, LP5523_REG_MASTER_FADER_BASE + nr - 1,
			   (u8)val);
	mutex_unlock(&chip->lock);

	if (ret == 0)
		ret = len;

	return ret;
}
