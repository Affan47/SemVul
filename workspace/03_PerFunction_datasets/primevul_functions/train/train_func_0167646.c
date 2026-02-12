static void garmin_nmea_event_hook(struct gps_device_t *session,
				   event_t event)
{
    if (session->context->readonly)
	return;

    if (event == event_driver_switch) {

	session->packet.counter = 0;
    }
    if (event == event_configure) {


	switch (session->packet.counter) {
	case 0:


	    (void)nmea_send(session, "$PGRMC,A,,100,,,,,,A,,1,2,1,30");
	    break;
	case 1:

	    (void)nmea_send(session, "$PGRMC1,1,1,1,,,,2,W,N");
	    break;
	case 2:

	    (void)nmea_send(session, "$PGRMC1E");
	    break;
	case 3:

	    (void)nmea_send(session, "$PGRMO,,2");
	    (void)nmea_send(session, "$PGRMO,GPGGA,1");
	    break;
	case 4:

	    (void)nmea_send(session, "$PGRMO,GPGSA,1");
	    break;
	case 5:
	    (void)nmea_send(session, "$PGRMO,GPGSV,1");
	    break;
	case 6:
	    (void)nmea_send(session, "$PGRMO,GPRMC,1");
	    break;
	case 7:
	    (void)nmea_send(session, "$PGRMO,PGRME,1");
	    break;
	}
    }
}
