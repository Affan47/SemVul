max11801_ts_interrupt(int irq, void *dev_id)
{
	struct max11801_data *data = dev_id;
	struct i2c_client *client = data->client;
	int status, i, ret;
	u8 buf[XY_BUFSIZE];
	int x = -1;
	int y = -1;

	status = read_register(data->client, GENERNAL_STATUS_REG);

	if (status & (MAX11801_FIFO_INT | MAX11801_FIFO_OVERFLOW)) {
		status = read_register(data->client, GENERNAL_STATUS_REG);

		ret = i2c_smbus_read_i2c_block_data(client, FIFO_RD_CMD,
						    XY_BUFSIZE, buf);


		if (ret < XY_BUFSIZE)
			goto out;

		for (i = 0; i < XY_BUFSIZE; i += XY_BUFSIZE / 2) {
			if ((buf[i + 1] & MEASURE_TAG_MASK) == MEASURE_X_TAG)
				x = (buf[i] << XY_BUF_OFFSET) +
				    (buf[i + 1] >> XY_BUF_OFFSET);
			else if ((buf[i + 1] & MEASURE_TAG_MASK) == MEASURE_Y_TAG)
				y = (buf[i] << XY_BUF_OFFSET) +
				    (buf[i + 1] >> XY_BUF_OFFSET);
		}

		if ((buf[1] & EVENT_TAG_MASK) != (buf[3] & EVENT_TAG_MASK))
			goto out;

		switch (buf[1] & EVENT_TAG_MASK) {
		case EVENT_INIT:

		case EVENT_MIDDLE:
			input_report_abs(data->input_dev, ABS_X, x);
			input_report_abs(data->input_dev, ABS_Y, y);
			input_event(data->input_dev, EV_KEY, BTN_TOUCH, 1);
			input_sync(data->input_dev);
			break;

		case EVENT_RELEASE:
			input_event(data->input_dev, EV_KEY, BTN_TOUCH, 0);
			input_sync(data->input_dev);
			break;

		case EVENT_FIFO_END:
			break;
		}
	}
out:
	return IRQ_HANDLED;
}
