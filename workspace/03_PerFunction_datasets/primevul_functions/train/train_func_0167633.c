static void garmin_mode_switch(struct gps_device_t *session, int mode)

{
    if (mode == MODE_BINARY) {
	(void)nmea_send(session, "$PGRMC1,1,2,1,,,,2,W,N");
	(void)nmea_send(session, "$PGRMI,,,,,,,R");
	(void)usleep(333);
	session->gpsdata.dev.driver_mode = MODE_BINARY;
    }
}
