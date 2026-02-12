static void set_nested(REgg *egg, const char *s) {
	int i = 0;
	if (CTX < 1) {
		return;
	}
	free (egg->lang.nested[CTX]);
	egg->lang.nested[CTX] = strdup (s);


	for (i = 1; i < 10; i++) {

		R_FREE (egg->lang.nested[CTX + i]);
	}
}
