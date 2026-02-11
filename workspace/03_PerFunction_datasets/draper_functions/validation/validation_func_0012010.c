verify_gov(char *new_gov, char *passed_gov)
{
	unsigned int i, j=0;

	if (!passed_gov || (strlen(passed_gov) > 19))
		return -EINVAL;

	strncpy(new_gov, passed_gov, 20);
	for (i=0;i<20;i++) {
		if (j) {
			new_gov[i] = '\0';
			continue;
		}
		if ((new_gov[i] >= 'a') && (new_gov[i] <= 'z')) {
			continue;
		}
		if ((new_gov[i] >= 'A') && (new_gov[i] <= 'Z')) {
			continue;
		}
		if (new_gov[i] == '-') {
			continue;
		}
		if (new_gov[i] == '_') {
			continue;
		}
		if (new_gov[i] == '\0') {
			j = 1;
			continue;
		}
		return -EINVAL;
	}
	new_gov[19] = '\0';
	return 0;
}
