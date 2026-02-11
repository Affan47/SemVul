gda_connection_clear_events_list (GdaConnection *cnc)
{
	g_return_if_fail (GDA_IS_CONNECTION (cnc));
	gda_connection_lock ((GdaLockable*) cnc);
	_clear_connection_events (cnc);
	gda_connection_unlock ((GdaLockable*) cnc);
}
