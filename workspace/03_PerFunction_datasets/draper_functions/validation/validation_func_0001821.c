isl29028_write_raw(struct iio_dev *indio_dev,
	     struct iio_chan_spec const *chan, int val, int val2, long mask)
{
	struct isl29028_chip *chip = iio_priv(indio_dev);
	int ret = -EINVAL;

	mutex_lock(&chip->lock);
	switch (chan->type) {
	case IIO_PROXIMITY:
		if (mask != IIO_CHAN_INFO_SAMP_FREQ) {
			dev_err(chip->dev,
				"proximity: mask value 0x%08lx not supported\n",
				mask);
			break;
		}
		if (val < 1 || val > 100) {
			dev_err(chip->dev,
				"Samp_freq %d is not in range[1:100]\n", val);
			break;
		}
		ret = isl29028_set_proxim_sampling(chip, val);
		if (ret < 0) {
			dev_err(chip->dev,
				"Setting proximity samp_freq fail, err %d\n",
				ret);
			break;
		}
		chip->prox_sampling = val;
		break;

	case IIO_LIGHT:
		if (mask != IIO_CHAN_INFO_SCALE) {
			dev_err(chip->dev,
				"light: mask value 0x%08lx not supported\n",
				mask);
			break;
		}
		if ((val != 125) && (val != 2000)) {
			dev_err(chip->dev,
				"lux scale %d is invalid [125, 2000]\n", val);
			break;
		}
		ret = isl29028_set_als_scale(chip, val);
		if (ret < 0) {
			dev_err(chip->dev,
				"Setting lux scale fail with error %d\n", ret);
			break;
		}
		chip->lux_scale = val;
		break;

	default:
		dev_err(chip->dev, "Unsupported channel type\n");
		break;
	}
	mutex_unlock(&chip->lock);
	return ret;
}
