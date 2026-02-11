cgiFormDouble(
        char *name, double *result, double defaultV) {
	cgiFormEntry *e;
	int ch;
	e = cgiFormEntryFindFirst(name);
	if (!e) {
		*result = defaultV;
		return cgiFormNotFound;
	}
	if (!strlen(e->value)) {
		*result = defaultV;
		return cgiFormEmpty;
	}
	ch = cgiFirstNonspaceChar(e->value);
	if (!(isdigit(ch)) && (ch != '.') && (ch != '-') && (ch != '+')) {
		*result = defaultV;
		return cgiFormBadType;
	} else {
		*result = atof(e->value);
		return cgiFormSuccess;
	}
}
