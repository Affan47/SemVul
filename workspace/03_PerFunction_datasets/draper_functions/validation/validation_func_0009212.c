free_smartphone_context_location_update_accuracy_from_string (const char* str, GError** error) {
	FreeSmartphoneContextLocationUpdateAccuracy value = 0;
	if (strcmp (str, "invalid") == 0) {
		value = FREE_SMARTPHONE_CONTEXT_LOCATION_UPDATE_ACCURACY_INVALID;
	} else if (strcmp (str, "navigation") == 0) {
		value = FREE_SMARTPHONE_CONTEXT_LOCATION_UPDATE_ACCURACY_NAVI;
	} else if (strcmp (str, "best") == 0) {
		value = FREE_SMARTPHONE_CONTEXT_LOCATION_UPDATE_ACCURACY_BEST;
	} else if (strcmp (str, "nearest-ten-meters") == 0) {
		value = FREE_SMARTPHONE_CONTEXT_LOCATION_UPDATE_ACCURACY_10M;
	} else if (strcmp (str, "hundred-meters") == 0) {
		value = FREE_SMARTPHONE_CONTEXT_LOCATION_UPDATE_ACCURACY_100M;
	} else if (strcmp (str, "one-kilometer") == 0) {
		value = FREE_SMARTPHONE_CONTEXT_LOCATION_UPDATE_ACCURACY_1KM;
	} else if (strcmp (str, "three-kilometers") == 0) {
		value = FREE_SMARTPHONE_CONTEXT_LOCATION_UPDATE_ACCURACY_3KM;
	} else if (strcmp (str, "hundred-kilometers") == 0) {
		value = FREE_SMARTPHONE_CONTEXT_LOCATION_UPDATE_ACCURACY_100KM;
	} else {
		g_set_error (error, G_DBUS_ERROR, G_DBUS_ERROR_INVALID_ARGS, "Invalid value for enum `FreeSmartphoneContextLocationUpdateAccuracy'");
	}
	return value;
}
