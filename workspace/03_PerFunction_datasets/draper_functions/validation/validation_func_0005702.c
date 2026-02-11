whitebalance_active(struct v4lprocessing_data *data)
{
	int wb;

	wb = v4lcontrol_get_ctrl(data->control, V4LCONTROL_WHITEBALANCE);
	if (!wb) {

		data->green_avg = 0;
	}

	return wb;
}
