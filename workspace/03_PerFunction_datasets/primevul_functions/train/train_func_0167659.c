static void fv18_event_hook(struct gps_device_t *session, event_t event)
{
    if (session->context->readonly)
	return;


    if (event == event_identified || event == event_reactivate)
	(void)nmea_send(session,
			"$PFEC,GPint,GSA01,DTM00,ZDA01,RMC01,GLL00,VTG00,GSV05");
}
