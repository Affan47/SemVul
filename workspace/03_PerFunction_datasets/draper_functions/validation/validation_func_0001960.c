get_filestream(struct ast_format_def *fmt, FILE *bfile)
{
	struct ast_filestream *s;

	int l = sizeof(*s) + fmt->buf_size + fmt->desc_size;
	if ( (s = ao2_alloc(l, filestream_destructor)) == NULL)
		return NULL;
	s->fmt = fmt;
	s->f = bfile;

	if (fmt->desc_size)
		s->_private = ((char *)(s + 1)) + fmt->buf_size;
	if (fmt->buf_size)
		s->buf = (char *)(s + 1);
	s->fr.src = fmt->name;
	return s;
}
