free_if_empty(char *s)
{
	if ((s != NULL) && (strlen(s) == 0)) {
		talloc_free(s);
		s = NULL;
	}
	return s;
}
