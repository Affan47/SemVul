so_call_rsync_finished(options_t *options_p, const char *inclistfile, const char *exclistfile) {
	int ret0, ret1;
	if(inclistfile == NULL) {
		printf_e("Error: inclistfile == NULL.");
		return EINVAL;
	}

	printf_ddd("Debug3: unlink()-ing \"%s\"\n", inclistfile);
	ret0 = unlink(inclistfile);

	if(options_p->flags[RSYNCPREFERINCLUDE])
		return ret0;

	if(exclistfile == NULL) {
		printf_e("Error: exclistfile == NULL.");
		return EINVAL;
	}

	printf_ddd("Debug3: unlink()-ing \"%s\"\n", exclistfile);
	ret1 = unlink(exclistfile);

	return ret0 == 0 ? ret1 : ret0;
}
