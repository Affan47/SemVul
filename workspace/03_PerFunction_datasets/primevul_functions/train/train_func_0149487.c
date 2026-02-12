static int unsolicited_report_interval(struct in_device *in_dev)
{
	int interval_ms, interval_jiffies;

	if (IGMP_V1_SEEN(in_dev) || IGMP_V2_SEEN(in_dev))
		interval_ms = IN_DEV_CONF_GET(
			in_dev,
			IGMPV2_UNSOLICITED_REPORT_INTERVAL);
	else
		interval_ms = IN_DEV_CONF_GET(
			in_dev,
			IGMPV3_UNSOLICITED_REPORT_INTERVAL);

	interval_jiffies = msecs_to_jiffies(interval_ms);


	if (interval_jiffies <= 0)
		interval_jiffies = 1;
	return interval_jiffies;
}
