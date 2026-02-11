get_status (GcIfaceGeoclue *gc,
	    GeoclueStatus  *status,
	    GError        **error)
{
	GeoclueAccuracyLevel level;

	geoclue_accuracy_get_details (GEOCLUE_MANUAL (gc)->accuracy,
	                              &level, NULL, NULL);
	if (level == GEOCLUE_ACCURACY_LEVEL_NONE) {
		*status = GEOCLUE_STATUS_UNAVAILABLE;
	} else {
		*status = GEOCLUE_STATUS_AVAILABLE;
	}
	return TRUE;
}
