static void nmea_mode_switch(struct gps_device_t *session, int mode)
{


    if (mode == MODE_BINARY)
    {
	const struct gps_type_t **dp;


	for (dp = gpsd_drivers; *dp; dp++) {
	    if ((*dp)->packet_type > 0 && (*dp)->packet_type != session->packet.type &&
	    	    (session->observed & PACKET_TYPEMASK((*dp)->packet_type))!=0) {
		(*dp)->mode_switcher(session, mode);
		break;
	    }
	}

    }
}
