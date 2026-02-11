hdup_inclist(phost_t host, int s)
{


	char *inc_day, *inc_week, *inc_month = NULL;

	if (s == REMOTE) {
		LOG("%s","Internal error: wrong function call...");
		hdup_cleanup(1, host);
	}

	inc_month = g_strdup_printf("%s/inclist.%s", host->dirname_etc,scheme[MONTHLY]);
	inc_week = g_strdup_printf("%s/inclist.%s", host->dirname_etc,scheme[WEEKLY]);
	inc_day = g_strdup_printf("%s/inclist.%s", host->dirname_etc, scheme[DAILY]);

	switch (s) {
		case MONTHLY:
			host->inclist = inc_month;

			hdup_unlink(host->inclist);
			hdup_unlink(inc_week);
			hdup_unlink(inc_day);
			g_free (inc_week); g_free(inc_day);
			break;
		case WEEKLY:
			host->inclist = inc_week;
			if (g_file_test(inc_month, G_FILE_TEST_IS_REGULAR)) {

				if (hdup_cp(inc_month,inc_week) != 0 )
					WARN("%s", "Failed to copy, performing full dump");
				hdup_unlink(inc_day);
			} else {
				if ( host->always == 0 )  {

					WARN("%s", "Could not find previous backup list");
					WARN("%s", "Backups must be made in order: monthly, weekly and then a daily");
					(void)rmdir(host->dirname_date);
					hdup_cleanup(-1,host);
				} else {

					VERBOSE("%s", "Scheme override weekly -> monthly");
					hdup_overview("Scheme","override weekly -> monthly");
					return hdup_inclist(host, MONTHLY);
				}
			}
			g_free(inc_month); g_free(inc_day);
			break;
		case DAILY:
			host->inclist = inc_day;
			if (g_file_test(inc_week, G_FILE_TEST_IS_REGULAR)) {
				VERBOSE("Copying %s over to daily", inc_week);

				if ( hdup_cp(inc_week,inc_day ) != 0 )
					WARN("%s","failed to copy, performing full dump");
			} else {
				if ( host->always == 0 ) {

					WARN("%s","could not find previous backup list");
					rmdir(host->dirname_date);
					hdup_cleanup(-1,host);
				} else {

					VERBOSE("%s", "Scheme override daily -> weekly");
					hdup_overview("Scheme","override daily -> weekly");
					return hdup_inclist(host, WEEKLY);
				}
			}
			g_free(inc_month); g_free(inc_week);
			break;
	}

	(void)hdup_chown(host->inclist, host->user, host->group);
	VERBOSE("Using inclist %s", host->inclist);
	return s;
}
