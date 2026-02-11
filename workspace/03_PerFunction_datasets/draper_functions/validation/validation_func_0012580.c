iio_update_demux(struct iio_dev *indio_dev)
{
	struct iio_buffer *buffer;
	int ret;

	list_for_each_entry(buffer, &indio_dev->buffer_list, buffer_list) {
		ret = iio_buffer_update_demux(indio_dev, buffer);
		if (ret < 0)
			goto error_clear_mux_table;
	}
	return 0;

error_clear_mux_table:
	list_for_each_entry(buffer, &indio_dev->buffer_list, buffer_list)
		iio_buffer_demux_free(buffer);

	return ret;
}
