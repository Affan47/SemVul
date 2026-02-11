ScanOptions() {

	if (globalreg->kismet_config->FetchOpt("gpsmodelock") == "true") {
		_MSG("Enabling GPS position information override (override broken GPS "
			 "units that always report 0 in the NMEA stream)", MSGFLAG_INFO);
		SetOptions(GPSD_OPT_FORCEMODE);
	}

	if (globalreg->kismet_config->FetchOpt("gpsreconnect") == "true") {
		_MSG("Enabling reconnection to the GPS device if the link is lost",
			 MSGFLAG_INFO);
		reconnect_attempt = 0;
	}

	return 1;
}
