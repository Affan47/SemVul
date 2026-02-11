bmc150_magn_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	struct bmc150_magn_data *data = iio_priv(indio_dev);
	int ret, tmp;
	s32 values[AXIS_XYZ_MAX];

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (iio_buffer_enabled(indio_dev))
			return -EBUSY;
		mutex_lock(&data->mutex);

		ret = bmc150_magn_set_power_state(data, true);
		if (ret < 0) {
			mutex_unlock(&data->mutex);
			return ret;
		}

		ret = bmc150_magn_read_xyz(data, values);
		if (ret < 0) {
			bmc150_magn_set_power_state(data, false);
			mutex_unlock(&data->mutex);
			return ret;
		}
		*val = values[chan->scan_index];

		ret = bmc150_magn_set_power_state(data, false);
		if (ret < 0) {
			mutex_unlock(&data->mutex);
			return ret;
		}

		mutex_unlock(&data->mutex);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:


		*val = 0;
		*val2 = 625;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = bmc150_magn_get_odr(data, val);
		if (ret < 0)
			return ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		switch (chan->channel2) {
		case IIO_MOD_X:
		case IIO_MOD_Y:
			ret = regmap_read(data->regmap, BMC150_MAGN_REG_REP_XY,
					  &tmp);
			if (ret < 0)
				return ret;
			*val = BMC150_MAGN_REGVAL_TO_REPXY(tmp);
			return IIO_VAL_INT;
		case IIO_MOD_Z:
			ret = regmap_read(data->regmap, BMC150_MAGN_REG_REP_Z,
					  &tmp);
			if (ret < 0)
				return ret;
			*val = BMC150_MAGN_REGVAL_TO_REPZ(tmp);
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}
