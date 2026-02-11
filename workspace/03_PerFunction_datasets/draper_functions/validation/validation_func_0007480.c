volgen_apply_filters (char *orig_volfile)
{
	DIR           *filterdir = NULL;
	struct dirent  entry = {0,};
	struct dirent *next = NULL;
	char          *filterpath = NULL;
	struct stat    statbuf = {0,};

	filterdir = opendir(FILTERDIR);
	if (!filterdir) {
		return;
	}

	while ((readdir_r(filterdir,&entry,&next) == 0) && next) {
		if (!strncmp(entry.d_name,".",sizeof(entry.d_name))) {
			continue;
		}
		if (!strncmp(entry.d_name,"..",sizeof(entry.d_name))) {
			continue;
		}


		if (gf_asprintf(&filterpath,"%s/%.*s",FILTERDIR,
				sizeof(entry.d_name), entry.d_name) == (-1)) {
			continue;
		}

		if (stat(filterpath,&statbuf) == (-1)) {
			goto free_fp;
		}
		if (!S_ISREG(statbuf.st_mode)) {
			goto free_fp;
		}


		if (access(filterpath,X_OK) != 0) {
			goto free_fp;
		}
		if (runcmd(filterpath,orig_volfile,NULL)) {
			gf_log("",GF_LOG_ERROR,"failed to run filter %.*s",
			       (int)sizeof(entry.d_name), entry.d_name);
		}
free_fp:
		GF_FREE(filterpath);
	}
}
