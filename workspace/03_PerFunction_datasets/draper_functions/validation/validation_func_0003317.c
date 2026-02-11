str_print_indent(__isl_take isl_printer *p,
	int indent)
{
	int i;

	if (p->buf_n + indent + 1 >= p->buf_size && grow_buf(p, indent))
		goto error;
	for (i = 0; i < indent; ++i)
		p->buf[p->buf_n++] = ' ';
	return p;
error:
	isl_printer_free(p);
	return NULL;
}
