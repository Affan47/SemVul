apol_tcl_malloc_to_new(char *s) {
		if (s == NULL) {
			return new char[0];
		}
		char *t = new char[strlen(s) + 1];
		strcpy(t, s);
		free(s);
		return t;
	}
