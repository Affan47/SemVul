static void nmea_event_hook(struct gps_device_t *session, event_t event)
{
    if (session->context->readonly)
	return;


    if (event == event_configure) {


	switch (session->packet.counter) {
#ifdef NMEA_ENABLE
	case 0:

	    gpsd_report(LOG_PROG, "=> Probing for Garmin NMEA\n");
	    (void)nmea_send(session, "$PGRMCE");
	    break;
#endif
#ifdef SIRF_ENABLE
	case 1:


	    gpsd_report(LOG_PROG, "=> Probing for SiRF\n");
	    (void)nmea_send(session,
			    "$PSRF100,0,%d,%d,%d,0",
			    session->gpsdata.dev.baudrate,
			    9 - session->gpsdata.dev.stopbits,
			    session->gpsdata.dev.stopbits);
	    session->back_to_nmea = true;
	    break;
#endif
#ifdef NMEA_ENABLE
	case 2:

	    gpsd_report(LOG_PROG, "=> Probing for FV-18\n");
	    (void)nmea_send(session, "$PFEC,GPint");
	    break;
	case 3:

	    gpsd_report(LOG_PROG, "=> Probing for Trimble Copernicus\n");
	    (void)nmea_send(session, "$PTNLSNM,0139,01");
	    break;
#endif
#ifdef EVERMORE_ENABLE
	case 4:
	    gpsd_report(LOG_PROG, "=> Probing for Evermore\n");


	    (void)gpsd_write(session,
			     "\x10\x02\x12\x8E\x7F\x01\x01\x00\x01\x01\x01\x00\x01\x00\x00\x00\x00\x00\x00\x13\x10\x03",
			     22);
	    break;
#endif
#ifdef GPSCLOCK_ENABLE
	case 5:

	    gpsd_report(LOG_PROG, "=> Probing for GPSClock\n");
	    (void)nmea_send(session, "$PFEC,GPsrq");
	    break;
#endif
#ifdef ASHTECH_ENABLE
	case 6:

	    gpsd_report(LOG_PROG, "=> Probing for Ashtech\n");
	    (void)nmea_send(session, "$PASHQ,RID");
	    break;
#endif
#ifdef UBX_ENABLE
	case 7:

	    gpsd_report(LOG_PROG, "=> Probing for UBX\n");
	    (void)ubx_write(session, 0x0au, 0x04, NULL, 0);
	    break;
#endif
#ifdef MTK3301_ENABLE
	case 8:

	    gpsd_report(LOG_PROG, "=> Probing for MediaTek\n");
	    (void)nmea_send(session, "$PMTK605");
	    break;
#endif
	default:
	    break;
	}
    }
}
