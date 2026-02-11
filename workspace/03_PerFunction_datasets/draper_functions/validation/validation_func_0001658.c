check_for_modules(const char *fs_name)
{
#ifdef __linux__
	struct utsname	uts;
	FILE		*f;
	char		buf[1024], *cp;
	int		namesz;

	if (uname(&uts))
		return (0);
	snprintf(buf, sizeof(buf), "/lib/modules/%s/modules.dep", uts.release);

	f = fopen(buf, "r");
	if (!f)
		return (0);

	namesz = strlen(fs_name);

	while (!feof(f)) {
		if (!fgets(buf, sizeof(buf), f))
			break;
		if ((cp = strchr(buf, ':')) != NULL)
			*cp = 0;
		else
			continue;
		if ((cp = strrchr(buf, '/')) != NULL)
			cp++;
		else
			cp = buf;
		if (!strncmp(cp, fs_name, namesz) &&
		    (!strcmp(cp + namesz, ".ko") ||
		     !strcmp(cp + namesz, ".ko.gz"))) {
			fclose(f);
			return (1);
		}
	}
	fclose(f);
#endif
	return (0);
}
