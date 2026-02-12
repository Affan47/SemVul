static void mtk3301_event_hook(struct gps_device_t *session, event_t event)
{


    if (session->context->readonly)
	return;

    if (event == event_identified) {
	(void)nmea_send(session, "$PMTK320,0");
	(void)nmea_send(session, "$PMTK300,1000,0,0,0.0,0.0");
	(void)nmea_send(session,
			"$PMTK314,0,1,0,1,1,5,1,1,0,0,0,0,0,0,0,0,0,1,0");
	(void)nmea_send(session, "$PMTK301,2");
	(void)nmea_send(session, "$PMTK313,1");
    }
}
