isl_printer_to_file(isl_ctx *ctx, FILE *file)
{
	struct isl_printer *p = isl_alloc_type(ctx, struct isl_printer);
	if (!p)
		return NULL;
	p->ctx = ctx;
	isl_ctx_ref(p->ctx);
	p->ops = &file_ops;
	p->file = file;
	p->buf = NULL;
	p->buf_n = 0;
	p->buf_size = 0;
	p->indent = 0;
	p->output_format = ISL_FORMAT_ISL;
	p->prefix = NULL;
	p->suffix = NULL;
	p->width = 0;

	return p;
}
