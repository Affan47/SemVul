void fs_private_dir_copy(const char *private_dir, const char *private_run_dir, const char *private_list) {
	assert(private_dir);
	assert(private_run_dir);
	assert(private_list);


	struct stat s;
	if (stat(private_dir, &s) == -1) {
		if (arg_debug)
			printf("Cannot find %s: %s\n", private_dir, strerror(errno));
		return;
	}


	mkdir_attr(private_run_dir, 0755, 0, 0);
	selinux_relabel_path(private_run_dir, private_dir);
	fs_logger2("tmpfs", private_dir);

	fs_logger_print();


	if (*private_list != '\0') {
		if (arg_debug)
			printf("Copying files in the new %s directory:\n", private_dir);


		char *dlist = strdup(private_list);
		if (!dlist)
			errExit("strdup");


		char *ptr = strtok(dlist, ",");
		if (!ptr) {
			fprintf(stderr, "Error: invalid private %s argument\n", private_dir);
			exit(1);
		}
		duplicate(ptr, private_dir, private_run_dir);

		while ((ptr = strtok(NULL, ",")) != NULL)
			duplicate(ptr, private_dir, private_run_dir);
		free(dlist);
		fs_logger_print();
	}
}
