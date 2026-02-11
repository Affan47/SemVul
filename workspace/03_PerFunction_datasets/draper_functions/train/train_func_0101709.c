accuracy_changed(
	DBusGProxy *proxy,
	int fields,
	double pdop,
	double hdop,
	double vdop,
	gpointer user_data
)
{
	accuracy_fields = fields;
	accuracy_pdop   = pdop;
	accuracy_hdop   = hdop;
	accuracy_vdop   = vdop;

	INFO(GYPSY_ACCURACY": AccuracyChanged(pdop=%f, hdop=%f, vdop=%f)",
		ACCURACY_PDOP_IS_VALID ? accuracy_pdop : NAN,
		ACCURACY_HDOP_IS_VALID ? accuracy_hdop : NAN,
		ACCURACY_VDOP_IS_VALID ? accuracy_vdop : NAN);

	g_string_truncate(nmea_gga, 0);
	g_string_truncate(nmea_gsa, 0);

	queue_send_nmea_to_clients();
	queue_send_info_to_clients();
}
