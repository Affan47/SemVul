tw_poll_status(TW_Device_Extension *tw_dev, u32 flag, int seconds)
{
	u32 status_reg_value;
	unsigned long before;
	int retval = 1;

	status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));
	before = jiffies;

	if (tw_check_bits(status_reg_value))
		tw_decode_bits(tw_dev, status_reg_value, 0);

	while ((status_reg_value & flag) != flag) {
		status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));

		if (tw_check_bits(status_reg_value))
			tw_decode_bits(tw_dev, status_reg_value, 0);

		if (time_after(jiffies, before + HZ * seconds))
			goto out;

		msleep(50);
	}
	retval = 0;
out:
	return retval;
}
