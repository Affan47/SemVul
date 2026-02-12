static void normalize_protected_variable(char *varname TSRMLS_DC)
{
	char *s = varname, *index = NULL, *indexend = NULL, *p;


	while (*s == ' ') {
		s++;
	}


	if (s != varname) {
		memmove(varname, s, strlen(s)+1);
	}

	for (p = varname; *p && *p != '['; p++) {
		switch(*p) {
			case ' ':
			case '.':
				*p = '_';
				break;
		}
	}


	index = strchr(varname, '[');
	if (index) {
		index++;
		s = index;
	} else {
		return;
	}


	while (index) {
		while (*index == ' ' || *index == '\r' || *index == '\n' || *index=='\t') {
			index++;
		}
		indexend = strchr(index, ']');
		indexend = indexend ? indexend + 1 : index + strlen(index);

		if (s != index) {
			memmove(s, index, strlen(index)+1);
			s += indexend-index;
		} else {
			s = indexend;
		}

		if (*s == '[') {
			s++;
			index = s;
		} else {
			index = NULL;
		}
	}
	*s = '\0';
}
