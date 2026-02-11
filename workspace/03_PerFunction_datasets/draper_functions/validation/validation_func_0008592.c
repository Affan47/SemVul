gmtmgg_init (int year1)
{
	struct GMTMGG_TIME *gmt_struct = NULL;
	int dm[12];
	int year, this_year, month, m;
	gmt_struct = (struct GMTMGG_TIME *) GMT_memory (VNULL, (size_t)1, sizeof(struct GMTMGG_TIME), "gmtmgg_init");
	gmt_struct->first_year = year1;

	dm[0] = 0;
	dm[1] = 31;
	dm[2] = 28;
	dm[3] = 31;
	dm[4] = 30;
	dm[5] = 31;
	dm[6] = 30;
	dm[7] = 31;
	dm[8] = 31;
	dm[9] = 30;
	dm[10] = 31;
	dm[11] = 30;
	gmt_struct->daymon[0] = 0;
	for (year = 0, month = 0; year < 5; year++) {
		this_year = gmt_struct->first_year + year;
		if (this_year%4 == 0 && !(this_year%400 == 0)) dm[2] = 29;
		for (m = 1; m <= 12; m++) {
			month++;
			gmt_struct->daymon[month] = gmt_struct->daymon[month - 1] + dm[m - 1];
		}
   		dm[2] = 28;
   		dm[0] = 31;
   	}
	MGD77_first_1900 = MGD77_first_2000 = FALSE;

  	return (gmt_struct);
}
