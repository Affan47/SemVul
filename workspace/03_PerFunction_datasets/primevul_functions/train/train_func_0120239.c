void enum_version_nr(struct file_magic *fm)
{
	char *v;
	char version[16];

	fm->sysstat_extraversion = 0;

	strcpy(version, VERSION);


	if ((v = strtok(version, ".")) == NULL)
		return;
	fm->sysstat_version = atoi(v) & 0xff;


	if ((v = strtok(NULL, ".")) == NULL)
		return;
	fm->sysstat_patchlevel = atoi(v) & 0xff;


	if ((v = strtok(NULL, ".")) == NULL)
		return;
	fm->sysstat_sublevel = atoi(v) & 0xff;


	if ((v = strtok(NULL, ".")) == NULL)
		return;
	fm->sysstat_extraversion = atoi(v) & 0xff;
}
