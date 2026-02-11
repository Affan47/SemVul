da9052_rtc_get_alarm_status(struct da9052_rtc *rtc)
{
	int ret;

	ret = da9052_reg_read(rtc->da9052, DA9052_ALARM_Y_REG);
	if (ret < 0) {
		rtc_err(rtc, "Failed to read ALM: %d\n", ret);
		return ret;
	}

	return !!(ret&DA9052_ALARM_Y_ALARM_ON);
}
