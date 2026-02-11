make_diff(const poldiff_t * diff, poldiff_form_e form, const char *name)
{
	poldiff_bool_t *pb;
	int error;
	if ((pb = calloc(1, sizeof(*pb))) == NULL || (pb->name = strdup(name)) == NULL) {
		error = errno;
		bool_free(pb);
		ERR(diff, "%s", strerror(error));
		errno = error;
		return NULL;
	}
	pb->form = form;
	return pb;
}
