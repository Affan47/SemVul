parse_time (const gchar *time_string)
{
	guint hours, minutes;
	gdouble seconds;
	gchar *end_pointer;

	g_return_val_if_fail (time_string != NULL, 0);

	hours = strtoul (time_string, &end_pointer, 10);
	if (end_pointer != time_string + 2)
		return -1;

	minutes = strtoul (time_string + 3, &end_pointer, 10);
	if (end_pointer != time_string + 5)
		return -1;

	seconds = g_ascii_strtod (time_string + 6, &end_pointer);
	if (end_pointer != time_string + strlen (time_string))
		return -1;

	return (gint64) ((seconds + minutes * 60 + hours * 3600) * 1000);
}
