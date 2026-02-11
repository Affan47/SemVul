gfarm_iobuffer_get_read_x(struct gfarm_iobuffer *b, void *data,
			  int len, int just)
{
	char *p;
	int rv, residual, tmp, *justp = just ? &tmp : NULL;

	for (p = data, residual = len; residual > 0; residual -= rv, p += rv) {
		if (IOBUFFER_IS_EMPTY(b)) {
			tmp = residual;
			gfarm_iobuffer_read(b, justp);
		}
		rv = gfarm_iobuffer_get(b, p, residual);
		if (rv == 0)
			break;
	}
	return (len - residual);
}
