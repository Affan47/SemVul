gdata_calendar_query_set_recurrence_expansion_start (GDataCalendarQuery *self, gint64 start)
{
	g_return_if_fail (GDATA_IS_CALENDAR_QUERY (self));
	g_return_if_fail (start >= -1);

	self->priv->recurrence_expansion_start = start;
	g_object_notify (G_OBJECT (self), "recurrence-expansion-start");


	gdata_query_set_etag (GDATA_QUERY (self), NULL);
}
