convert_to_working_tree_internal(const char *path, const char *src,
					    size_t len, struct strbuf *dst,
					    int normalizing)
{
	int ret = 0;
	const char *filter = NULL;
	struct conv_attrs ca;

	convert_attrs(&ca, path);
	if (ca.drv)
		filter = ca.drv->smudge;

	ret |= ident_to_worktree(path, src, len, dst, ca.ident);
	if (ret) {
		src = dst->buf;
		len = dst->len;
	}


	if (filter || !normalizing) {
		ca.crlf_action = input_crlf_action(ca.crlf_action, ca.eol_attr);
		ret |= crlf_to_worktree(path, src, len, dst, ca.crlf_action);
		if (ret) {
			src = dst->buf;
			len = dst->len;
		}
	}
	return ret | apply_filter(path, src, len, dst, filter);
}
