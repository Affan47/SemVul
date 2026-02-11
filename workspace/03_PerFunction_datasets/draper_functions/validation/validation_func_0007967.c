vcc_file_source(const struct vcc *tl, struct vsb *sb, const char *fn)
{
	char *f;
	struct source *sp;

	f = vreadfile(tl->vcl_dir, fn, NULL);
	if (f == NULL) {
		VSB_printf(sb, "Cannot read file '%s': %s\n",
		    fn, strerror(errno));
		return (NULL);
	}
	sp = vcc_new_source(f, NULL, fn);
	sp->freeit = f;
	return (sp);
}
