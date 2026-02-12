R_API int r_str_split(char *str, char ch) {
	int i;
	char *p;
	if (!str || !*str) {
		return 0;
	}

	for (i = 1, p = str; *p; p++) {
		if (*p == ch) {
			i++;
			*p = '\0';
		}
	}
	return i;
}
