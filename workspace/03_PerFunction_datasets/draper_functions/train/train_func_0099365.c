match_str_list(char *str, char **list) {
	int i = 0, matched = 0;

	if (! str || ! list) {
		return 0;
	}
	while (list[i] != NULL) {
		if (!strcmp(list[i], "*")) {
			matched = 1;
			break;
		} else if (strstr(str, list[i])) {
			matched = 1;
			break;
		}
		i++;
	}
	return matched;
}
