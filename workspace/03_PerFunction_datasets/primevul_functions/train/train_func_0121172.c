int set_default_file(char *datafile, int d_off, int sa_name)
{
	char sa_dir[MAX_FILE_LEN];
	struct tm rectime = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL};
	int err = 0;


	if (datafile[0]) {
		strncpy(sa_dir, datafile, MAX_FILE_LEN);
	}
	else {
		strncpy(sa_dir, SA_DIR, MAX_FILE_LEN);
	}
	sa_dir[MAX_FILE_LEN - 1] = '\0';

	get_time(&rectime, d_off);
	if (sa_name < 0) {


		guess_sa_name(sa_dir, &rectime, &sa_name);
	}
	if (sa_name) {

		err = snprintf(datafile, MAX_FILE_LEN,
			       "%s/sa%04d%02d%02d", sa_dir,
			       rectime.tm_year + 1900,
			       rectime.tm_mon + 1,
			       rectime.tm_mday);
	}
	else {

		err = snprintf(datafile, MAX_FILE_LEN,
			       "%s/sa%02d", sa_dir,
			       rectime.tm_mday);
	}
	datafile[MAX_FILE_LEN - 1] = '\0';
	default_file_used = TRUE;

	return ((err < 0) || (err >= MAX_FILE_LEN));
}
