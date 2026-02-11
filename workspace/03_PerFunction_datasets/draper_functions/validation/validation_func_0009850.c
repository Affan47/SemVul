get_address (GcIfaceAddress   *gc,
             int              *timestamp,
             GHashTable      **address,
             GeoclueAccuracy **accuracy,
             GError          **error)
{
	GeoclueLocalnet *localnet;
	char *mac;
	Gateway *gw;

	localnet = GEOCLUE_LOCALNET (gc);


	mac = geoclue_connectivity_get_router_mac (localnet->conn);

	if (!mac) {
		g_warning ("Couldn't get current gateway mac address");
		if (error) {
			g_set_error (error, GEOCLUE_ERROR,
			             GEOCLUE_ERROR_NOT_AVAILABLE, "Could not get current gateway mac address");
		}
		return FALSE;
	}

	gw = geoclue_localnet_find_gateway (localnet, mac);
	g_free (mac);

	if (timestamp) {
		*timestamp = time(NULL);
	}
	if (address) {
		if (gw) {
			*address = geoclue_address_details_copy (gw->address);
		} else {
			*address = geoclue_address_details_new ();
		}
	}
	if (accuracy) {
		if (gw) {
			*accuracy = geoclue_accuracy_copy (gw->accuracy);
		} else {
			*accuracy = geoclue_accuracy_new (GEOCLUE_ACCURACY_LEVEL_NONE, 0, 0);
		}
	}
	return TRUE;
}
