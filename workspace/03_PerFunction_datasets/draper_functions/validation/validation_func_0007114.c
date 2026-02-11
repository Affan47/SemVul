read_date_from_file(struct tm *tm)
{
	int last_mday, last_mon, last_year;
	FILE *fp;

	if ((fp = fopen(_PATH_LASTDATE, "r"))) {
		if (fscanf(fp, "%d.%d.%d\n", &last_mday, &last_mon, &last_year)
		    == 3) {
			tm->tm_year = last_year - 1900;
			if ((tm->tm_mon << 5) + tm->tm_mday <
			    ((last_mon - 1) << 5) + last_mday)
				tm->tm_year++;
		}
		fclose(fp);
	}
	write_date_to_file(tm);
}
