ast_format_cap_add(struct ast_format_cap *cap, const struct ast_format *format)
{
	struct ast_format *fnew;

	if (!format || !format->id) {
		return;
	}
	if (!(fnew = ao2_alloc(sizeof(struct ast_format), NULL))) {
		return;
	}
	ast_format_copy(fnew, format);
	ao2_link(cap->formats, fnew);
	ao2_ref(fnew, -1);
}
