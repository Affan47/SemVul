int sa_get_record_timestamp_struct(unsigned int l_flags, struct record_header *record_hdr,
				   struct tm *rectime, struct tm *loctime)
{
	struct tm *ltm = NULL;
	int rc = 0;


	if (loctime) {
		ltm = localtime_r((const time_t *) &(record_hdr->ust_time), loctime);
		if (ltm) {

			*rectime = *loctime;
		}
		else {
			rc = 1;
		}
	}


	if (PRINT_LOCAL_TIME(l_flags) && !ltm) {

		ltm = localtime_r((const time_t *) &(record_hdr->ust_time), rectime);
	}

	if (!PRINT_LOCAL_TIME(l_flags) && !PRINT_TRUE_TIME(l_flags)) {


		ltm = gmtime_r((const time_t *) &(record_hdr->ust_time), rectime);
	}

	if (!ltm) {
		rc = 1;
	}

	if (PRINT_TRUE_TIME(l_flags)) {

		rectime->tm_hour = record_hdr->hour;
		rectime->tm_min  = record_hdr->minute;
		rectime->tm_sec  = record_hdr->second;
	}

	return rc;
}
