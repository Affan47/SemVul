ad5380_get_powerdown_mode(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan)
{
	struct ad5380_state *st = iio_priv(indio_dev);
	unsigned int mode;
	int ret;

	ret = regmap_read(st->regmap, AD5380_REG_SF_CTRL, &mode);
	if (ret)
		return ret;

	mode = (mode >> AD5380_CTRL_PWR_DOWN_MODE_OFFSET) & 1;

	return mode;
}
