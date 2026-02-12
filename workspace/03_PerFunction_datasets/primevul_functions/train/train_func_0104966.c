static int netns_add(int argc, char **argv, bool create)
{


	char netns_path[PATH_MAX], proc_path[PATH_MAX];
	const char *name;
	pid_t pid;
	int fd;
	int made_netns_run_dir_mount = 0;

	if (create) {
		if (argc < 1) {
			fprintf(stderr, "No netns name specified\n");
			return -1;
		}
	} else {
		if (argc < 2) {
			fprintf(stderr, "No netns name and PID specified\n");
			return -1;
		}

		if (get_s32(&pid, argv[1], 0) || !pid) {
			fprintf(stderr, "Invalid PID: %s\n", argv[1]);
			return -1;
		}
	}
	name = argv[0];

	snprintf(netns_path, sizeof(netns_path), "%s/%s", NETNS_RUN_DIR, name);

	if (create_netns_dir())
		return -1;


	while (mount("", NETNS_RUN_DIR, "none", MS_SHARED | MS_REC, NULL)) {

		if (errno != EINVAL || made_netns_run_dir_mount) {
			fprintf(stderr, "mount --make-shared %s failed: %s\n",
				NETNS_RUN_DIR, strerror(errno));
			return -1;
		}


		if (mount(NETNS_RUN_DIR, NETNS_RUN_DIR, "none", MS_BIND | MS_REC, NULL)) {
			fprintf(stderr, "mount --bind %s %s failed: %s\n",
				NETNS_RUN_DIR, NETNS_RUN_DIR, strerror(errno));
			return -1;
		}
		made_netns_run_dir_mount = 1;
	}


	fd = open(netns_path, O_RDONLY|O_CREAT|O_EXCL, 0);
	if (fd < 0) {
		fprintf(stderr, "Cannot create namespace file \"%s\": %s\n",
			netns_path, strerror(errno));
		return -1;
	}
	close(fd);

	if (create) {
		if (unshare(CLONE_NEWNET) < 0) {
			fprintf(stderr, "Failed to create a new network namespace \"%s\": %s\n",
				name, strerror(errno));
			goto out_delete;
		}

		strcpy(proc_path, "/proc/self/ns/net");
	} else {
		snprintf(proc_path, sizeof(proc_path), "/proc/%d/ns/net", pid);
	}


	if (mount(proc_path, netns_path, "none", MS_BIND, NULL) < 0) {
		fprintf(stderr, "Bind %s -> %s failed: %s\n",
			proc_path, netns_path, strerror(errno));
		goto out_delete;
	}
	return 0;
out_delete:
	if (create) {
		netns_delete(argc, argv);
	} else if (unlink(netns_path) < 0) {
		fprintf(stderr, "Cannot remove namespace file \"%s\": %s\n",
			netns_path, strerror(errno));
	}
	return -1;
}
