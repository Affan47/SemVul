get_ibmasmfs_mount_point(char *mount_point)
{
	FILE *f;
	char line[RSA_NAME_SIZE];
	char *first, *mount, *type;


	f = fopen("/proc/mounts", "r");
	if (f == NULL)
		return 1;

	while(fgets(line, 1024, f)) {
		first = strtok(line, " ");
		mount = strtok(NULL, " ");
		type = strtok(NULL, " ");
		if (!strcmp(type, "ibmasmfs")) {
			strncpy(mount_point, mount, RSA_NAME_SIZE - 1);
			fclose(f);
			return 0;
		}
	}
	fclose(f);
	return 1;
}
