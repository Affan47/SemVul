alarmtimer_rtc_add_device(struct device *dev,
				struct class_interface *class_intf)
{
	unsigned long flags;
	struct rtc_device *rtc = to_rtc_device(dev);

	if (rtcdev)
		return -EBUSY;

	if (!rtc->ops->set_alarm)
		return -1;
	if (!device_may_wakeup(rtc->dev.parent))
		return -1;

	spin_lock_irqsave(&rtcdev_lock, flags);
	if (!rtcdev) {
		rtcdev = rtc;

		get_device(dev);
	}
	spin_unlock_irqrestore(&rtcdev_lock, flags);
	return 0;
}
