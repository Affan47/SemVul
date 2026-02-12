static int get_alloted(char *me, char *intype, char *link,
		       struct alloted_s **alloted)
{
	int n, ret;
	char name[100], type[100], br[100];
	char **groups;
	FILE *fin;

	int count = 0;
	size_t len = 0;
	char *line = NULL;

	fin = fopen(LXC_USERNIC_CONF, "r");
	if (!fin) {
		usernic_error("Failed to open \"%s\": %s\n", LXC_USERNIC_CONF,
			      strerror(errno));
		return -1;
	}

	groups = get_groupnames();
	while ((getline(&line, &len, fin)) != -1) {
		ret = sscanf(line, "%99[^ \t] %99[^ \t] %99[^ \t] %d", name,
			     type, br, &n);
		if (ret != 4)
			continue;

		if (strlen(name) == 0)
			continue;

		if (strcmp(name, me)) {
			if (name[0] != '@')
				continue;

			if (!name_is_in_groupnames(name + 1, groups))
				continue;
		}

		if (strcmp(type, intype))
			continue;

		if (strcmp(link, br))
			continue;


		if (!append_alloted(alloted, name, n)) {
			count = 0;
			break;
		}
		count += n;
	}

	free_groupnames(groups);
	fclose(fin);
	free(line);


	return count;
}
