e_cal_tzlookup_ecal (const gchar *tzid,
                     gconstpointer custom,
                     GError **error)
{
	ECal *ecal = (ECal *) custom;
	icaltimezone *zone = NULL;
	GError *local_error = NULL;

	g_return_val_if_fail (ecal != NULL, NULL);
	g_return_val_if_fail (E_IS_CAL (ecal), NULL);

	if (e_cal_get_timezone (ecal, tzid, &zone, &local_error)) {
		g_warn_if_fail (local_error == NULL);
		return zone;
	}

	if (g_error_matches (local_error, E_CALENDAR_ERROR,
		E_CALENDAR_STATUS_OBJECT_NOT_FOUND)) {


		g_clear_error (&local_error);
	}

	g_propagate_error (error, local_error);

	return NULL;
}
