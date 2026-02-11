system_timezone_read_etc_localtime_hardlink (GHashTable *ical_zones)
{
	struct stat stat_localtime;
	gchar *retval, *fallback = NULL;

	if (g_stat (ETC_LOCALTIME, &stat_localtime) != 0)
		return NULL;

	if (!S_ISREG (stat_localtime.st_mode))
		return NULL;

	retval = recursive_compare (
		&stat_localtime,
		NULL,
		0,
		SYSTEM_ZONEINFODIR,
		files_are_identical_inode,
		ical_zones,
		0,
		&fallback);

	if (retval)
		g_free (fallback);
	else
		retval = fallback;

	return retval;
}
