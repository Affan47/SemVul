int check_alt_sa_dir(char *datafile, int d_off, int sa_name)
{
	struct stat sb;

	if (stat(datafile, &sb) == 0) {
		if (S_ISDIR(sb.st_mode)) {


			set_default_file(datafile, d_off, sa_name);
			return 1;
		}
	}

	return 0;
}
