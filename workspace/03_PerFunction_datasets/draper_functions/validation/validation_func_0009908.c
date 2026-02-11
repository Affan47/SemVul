find_line_by_number(struct unistim_device *d, const char *val) {
	struct unistim_line *l, *ret = NULL;

	AST_LIST_LOCK(&d->lines);
	AST_LIST_TRAVERSE(&d->lines, l, list) {
		if (!strcmp(l->name, val)) {
			ret = l;
			break;
		}
	}
	AST_LIST_UNLOCK(&d->lines);
	return ret;
}
