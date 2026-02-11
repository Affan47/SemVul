geoclue_plazes_get_position (GcIfacePosition        *iface,
                             GeocluePositionFields  *fields,
                             int                    *timestamp,
                             double                 *latitude,
                             double                 *longitude,
                             double                 *altitude,
                             GeoclueAccuracy       **accuracy,
                             GError                **error)
{
	GeocluePlazes *plazes;
	char *mac, *mac_lc;

	plazes = (GEOCLUE_PLAZES (iface));

	*fields = GEOCLUE_POSITION_FIELDS_NONE;
	if (timestamp) {
		*timestamp = time (NULL);
	}

	mac = geoclue_connectivity_get_router_mac (plazes->conn);
	if (mac == NULL) {
		g_set_error (error, GEOCLUE_ERROR,
		             GEOCLUE_ERROR_NOT_AVAILABLE,
		             "Router mac address query failed");
		geoclue_plazes_set_status (plazes, GEOCLUE_STATUS_ERROR);
		return FALSE;
	}

	mac = mac_strdown (mac);

	geoclue_plazes_set_status (plazes, GEOCLUE_STATUS_ACQUIRING);

	mac_lc = g_ascii_strdown (mac, -1);
	g_free (mac);
	if (!gc_web_service_query (plazes->web_service, error,
	                           PLAZES_KEY_MAC, mac,
	                           (char *)0)) {
		g_free (mac_lc);

		geoclue_plazes_set_status (plazes, GEOCLUE_STATUS_AVAILABLE);
		g_set_error (error, GEOCLUE_ERROR,
		             GEOCLUE_ERROR_NOT_AVAILABLE,
		             "Did not get reply from server");
		return FALSE;
	}

	g_free (mac);

	if (latitude && gc_web_service_get_double (plazes->web_service,
	                                           latitude, PLAZES_LAT_XPATH)) {
		*fields |= GEOCLUE_POSITION_FIELDS_LATITUDE;
	}
	if (longitude && gc_web_service_get_double (plazes->web_service,
	                                            longitude, PLAZES_LON_XPATH)) {
		*fields |= GEOCLUE_POSITION_FIELDS_LONGITUDE;
	}

	if (accuracy) {


        *accuracy = geoclue_accuracy_new (GEOCLUE_ACCURACY_LEVEL_STREET, 0, 0);
	}

    if (!(*fields & GEOCLUE_POSITION_FIELDS_LATITUDE &&
         *fields & GEOCLUE_POSITION_FIELDS_LONGITUDE)) {


		geoclue_plazes_set_status (plazes, GEOCLUE_STATUS_ERROR);
		g_set_error (error, GEOCLUE_ERROR,
		             GEOCLUE_ERROR_NOT_AVAILABLE,
		             "Could not understand reply from server");
		return FALSE;
    }

	geoclue_plazes_set_status (plazes, GEOCLUE_STATUS_AVAILABLE);

	return TRUE;
}
