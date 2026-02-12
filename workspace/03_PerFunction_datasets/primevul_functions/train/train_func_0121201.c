void guess_sa_name(char *sa_dir, struct tm *rectime, int *sa_name)
{
	char filename[MAX_FILE_LEN];
	struct stat sb;
	time_t sa_mtime;


	*sa_name = 0;


	snprintf(filename, MAX_FILE_LEN,
		 "%s/sa%04d%02d%02d", sa_dir,
		 rectime->tm_year + 1900,
		 rectime->tm_mon + 1,
		 rectime->tm_mday);
	filename[MAX_FILE_LEN - 1] = '\0';

	if (stat(filename, &sb) < 0)

		return;
	sa_mtime = sb.st_mtime;


	snprintf(filename, MAX_FILE_LEN,
		 "%s/sa%02d", sa_dir,
		 rectime->tm_mday);
	filename[MAX_FILE_LEN - 1] = '\0';

	if (stat(filename, &sb) < 0) {

		*sa_name = 1;
		return;
	}

	if (sa_mtime > sb.st_mtime) {

		*sa_name = 1;
	}
}
