el_init(const char *prog, FILE *fin, FILE *fout, FILE *ferr)
{
	EditLine *el = el_malloc(sizeof(*el));

	if (el == NULL)
		return NULL;

	memset(el, 0, sizeof(EditLine));

	el->el_infile = fin;
	el->el_outfile = fout;
	el->el_errfile = ferr;

	el->el_infd = fileno(fin);
	el->el_outfd = fileno(fout);
	el->el_errfd = fileno(ferr);

	el->el_prog = Strdup(ct_decode_string(prog, &el->el_scratch));
	if (el->el_prog == NULL) {
		el_free(el);
		return NULL;
	}


	el->el_flags = 0;
#ifdef WIDECHAR
	setlocale(LC_CTYPE, NULL);
        if (MB_CUR_MAX > 1)
		el->el_flags |= CHARSET_IS_MULTIBYTE;
#endif

	if (terminal_init(el) == -1) {
		el_free(el->el_prog);
		el_free(el);
		return NULL;
	}
	(void) keymacro_init(el);
	(void) map_init(el);
	if (tty_init(el) == -1)
		el->el_flags |= NO_TTY;
	(void) ch_init(el);
	(void) search_init(el);
	(void) hist_init(el);
	(void) prompt_init(el);
	(void) sig_init(el);
	(void) read_init(el);

	return el;
}
