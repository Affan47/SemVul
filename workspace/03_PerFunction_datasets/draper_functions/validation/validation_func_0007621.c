alter_cal_client (gpointer user_data)
{
	ECalClient *cal_client = user_data;
	GError *error = NULL;
	icalcomponent *icalcomp;
	struct icaltimetype now;
	gchar *uid = NULL;

	g_return_val_if_fail (cal_client != NULL, NULL);

	now = icaltime_current_time_with_zone (icaltimezone_get_utc_timezone ());
	icalcomp = icalcomponent_new (ICAL_VEVENT_COMPONENT);
	icalcomponent_set_summary (icalcomp, "Initial event summary");
	icalcomponent_set_dtstart (icalcomp, now);
	icalcomponent_set_dtend   (icalcomp, icaltime_from_timet (icaltime_as_timet (now) + 60 * 60 * 60, 0));

	if (!e_cal_client_create_object_sync (cal_client, icalcomp, &uid, NULL, &error))
		g_error ("create object sync: %s", error->message);

	icalcomponent_set_uid (icalcomp, uid);
	icalcomponent_set_summary (icalcomp, "Modified event summary");

	if (!e_cal_client_modify_object_sync (cal_client, icalcomp, E_CAL_OBJ_MOD_ALL, NULL, &error))
		g_error ("modify object sync: %s", error->message);

	if (!e_cal_client_remove_object_sync (cal_client, uid, NULL, E_CAL_OBJ_MOD_ALL, NULL, &error))
		g_error ("remove object sync: %s", error->message);

	g_free (uid);
	icalcomponent_free (icalcomp);

	return FALSE;
}
