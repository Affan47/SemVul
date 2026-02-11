xlnx_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);
	unsigned long new_time;

	new_time = rtc_tm_to_time64(tm);

	if (new_time > RTC_SEC_MAX_VAL)
		return -EINVAL;

	writel(new_time, xrtcdev->reg_base + RTC_SET_TM_WR);

	return 0;
}
