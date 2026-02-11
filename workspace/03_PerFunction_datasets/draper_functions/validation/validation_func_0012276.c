ast_load_realtime(const char *family, ...)
{
	struct ast_variable *res;
	struct ast_variable *cur;
	struct ast_variable **prev;
	va_list ap;

	va_start(ap, family);
	res = ast_load_realtime_helper(family, ap);
	va_end(ap);


	prev = &res;
	cur = res;
	while (cur) {
		if (ast_strlen_zero(cur->value)) {

			struct ast_variable *next;

			next = cur->next;
			*prev = next;
			ast_variable_destroy(cur);
			cur = next;
		} else {

			if (cur->value[0] == ' ' && cur->value[1] == '\0') {
				char *vptr = (char *) cur->value;

				vptr[0] = '\0';
			}

			prev = &cur->next;
			cur = cur->next;
		}
	}
	return res;
}
