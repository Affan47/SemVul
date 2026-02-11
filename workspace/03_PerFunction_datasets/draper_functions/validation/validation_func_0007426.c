tiadc_channel_init(struct iio_dev *indio_dev, int channels)
{
	struct tiadc_device *adc_dev = iio_priv(indio_dev);
	struct iio_chan_spec *chan_array;
	struct iio_chan_spec *chan;
	int i;

	indio_dev->num_channels = channels;
	chan_array = kcalloc(channels,
			sizeof(struct iio_chan_spec), GFP_KERNEL);
	if (chan_array == NULL)
		return -ENOMEM;

	chan = chan_array;
	for (i = 0; i < channels; i++, chan++) {

		chan->type = IIO_VOLTAGE;
		chan->indexed = 1;
		chan->channel = adc_dev->channel_line[i];
		chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
		chan->datasheet_name = chan_name_ain[chan->channel];
		chan->scan_index = i;
		chan->scan_type.sign = 'u';
		chan->scan_type.realbits = 12;
		chan->scan_type.storagebits = 16;
	}

	indio_dev->channels = chan_array;

	return 0;
}
