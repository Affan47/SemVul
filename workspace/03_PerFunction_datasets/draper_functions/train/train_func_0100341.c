pdf_free_ocg(fz_context *ctx, pdf_ocg_descriptor *desc)
{
	if (!desc)
		return;

	pdf_drop_obj(desc->intent);
	fz_free(ctx, desc->ocgs);
	fz_free(ctx, desc);
}
