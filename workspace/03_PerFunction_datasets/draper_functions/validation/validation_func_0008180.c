alarm_time_is_future (struct tm *tm, guint hour, guint minute, guint second)
{
	return (hour > tm->tm_hour ||
			(hour == tm->tm_hour && minute > tm->tm_min) ||
			(hour == tm->tm_hour && minute == tm->tm_min && second > tm->tm_sec));
}
