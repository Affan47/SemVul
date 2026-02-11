midgard_timestamp_transform_to_gda_timestamp(const GValue *src, GValue *dst)
{
	g_return_if_fail(G_VALUE_HOLDS(src, MGD_TYPE_TIMESTAMP) &&
			G_VALUE_HOLDS(dst, GDA_TYPE_TIMESTAMP));

	GdaTimestamp *gt = g_new0(GdaTimestamp, 1);
	MidgardTimestamp *mt = (MidgardTimestamp *) g_value_get_boxed(src);


	gt->year = mt->year;
	gt->month = mt->month;
	gt->day = mt->day;

	gt->hour = mt->hour;
	gt->minute = mt->minute;
	gt->second = mt->second;

	gt->timezone = mt->offset;

	gda_value_set_timestamp(dst, (const GdaTimestamp *)gt);

	g_free (gt);
}
