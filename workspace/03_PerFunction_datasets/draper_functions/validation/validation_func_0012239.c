max8997_rtc_start_alarm(struct max8997_rtc_info *info)
{
	u8 data[RTC_NR_TIME];
	int ret;

	if (!mutex_is_locked(&info->lock))
		dev_warn(info->dev, "%s: should have mutex locked\n", __func__);

	ret = max8997_bulk_read(info->rtc, MAX8997_RTC_ALARM1_SEC, RTC_NR_TIME,
				data);
	if (ret < 0) {
		dev_err(info->dev, "%s: fail to read alarm reg(%d)\n",
				__func__, ret);
		goto out;
	}

	data[RTC_SEC] |= (1 << ALARM_ENABLE_SHIFT);
	data[RTC_MIN] |= (1 << ALARM_ENABLE_SHIFT);
	data[RTC_HOUR] |= (1 << ALARM_ENABLE_SHIFT);
	data[RTC_WEEKDAY] &= ~ALARM_ENABLE_MASK;
	if (data[RTC_MONTH] & 0xf)
		data[RTC_MONTH] |= (1 << ALARM_ENABLE_SHIFT);
	if (data[RTC_YEAR] & 0x7f)
		data[RTC_YEAR] |= (1 << ALARM_ENABLE_SHIFT);
	if (data[RTC_DATE] & 0x1f)
		data[RTC_DATE] |= (1 << ALARM_ENABLE_SHIFT);

	ret = max8997_bulk_write(info->rtc, MAX8997_RTC_ALARM1_SEC, RTC_NR_TIME,
				 data);
	if (ret < 0) {
		dev_err(info->dev, "%s: fail to write alarm reg(%d)\n",
				__func__, ret);
		goto out;
	}

	ret = max8997_rtc_set_update_reg(info);
out:
	return ret;
}
