mms114_setup_regs(struct mms114_data *data)
{
	const struct mms114_platform_data *pdata = data->pdata;
	int val;
	int error;

	error = mms114_get_version(data);
	if (error < 0)
		return error;

	error = mms114_set_active(data, true);
	if (error < 0)
		return error;

	val = (pdata->x_size >> 8) & 0xf;
	val |= ((pdata->y_size >> 8) & 0xf) << 4;
	error = mms114_write_reg(data, MMS114_XY_RESOLUTION_H, val);
	if (error < 0)
		return error;

	val = pdata->x_size & 0xff;
	error = mms114_write_reg(data, MMS114_X_RESOLUTION, val);
	if (error < 0)
		return error;

	val = pdata->y_size & 0xff;
	error = mms114_write_reg(data, MMS114_Y_RESOLUTION, val);
	if (error < 0)
		return error;

	if (pdata->contact_threshold) {
		error = mms114_write_reg(data, MMS114_CONTACT_THRESHOLD,
				pdata->contact_threshold);
		if (error < 0)
			return error;
	}

	if (pdata->moving_threshold) {
		error = mms114_write_reg(data, MMS114_MOVING_THRESHOLD,
				pdata->moving_threshold);
		if (error < 0)
			return error;
	}

	return 0;
}
