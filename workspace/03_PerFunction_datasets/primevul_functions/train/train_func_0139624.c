static const char *find_alias(REgg *egg, const char *str) {

	char *p = (char *) str;
	int i;
	if (*str == '"') {
		return strdup (str);
	}

	while (*p && !is_space (*p)) {
		p++;
	}
	*p = '\x00';
	for (i = 0; i < egg->lang.nalias; i++) {
		if (!strcmp (str, egg->lang.aliases[i].name)) {
			return strdup (egg->lang.aliases[i].content);
		}
	}
	return NULL;

}
