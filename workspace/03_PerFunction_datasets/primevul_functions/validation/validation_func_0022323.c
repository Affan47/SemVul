term_set_output(char *dest)
{
    FILE *f = NULL;

    FPRINTF((stderr, "term_set_output\n"));
    assert(dest == NULL || dest != outstr);

    if (multiplot) {
	fputs("In multiplot mode you can't change the output\n", stderr);
	return;
    }
    if (term && term_initialised) {
	(*term->reset) ();
	term_initialised = FALSE;

	gppsfile = NULL;
    }
    if (dest == NULL) {
	term_close_output();
    } else {

#if defined(PIPES)
	if (*dest == '|') {
	    restrict_popen();
#if defined(_WIN32 ) || defined(MSDOS)
	    if (term && (term->flags & TERM_BINARY))
		f = popen(dest + 1, "wb");
	    else
		f = popen(dest + 1, "w");
#else
	    f = popen(dest + 1, "w");
#endif
	    if (f == (FILE *) NULL)
		os_error(c_token, "cannot create pipe; output not changed");
	    else
		output_pipe_open = TRUE;
	} else {
#endif

#ifdef _WIN32
	if (outstr && stricmp(outstr, "PRN") == 0) {

	    close_printer(gpoutfile);
	    gpoutfile = stdout;
	    free(outstr);
	    outstr = NULL;
	}
	if (stricmp(dest, "PRN") == 0) {
	    if ((f = open_printer()) == (FILE *) NULL)
		os_error(c_token, "cannot open printer temporary file; output may have changed");
	} else
#endif

	{
#if defined (MSDOS)
	    if (outstr && (0 == stricmp(outstr, dest))) {


		term_close_output();
	    }
#endif
	    if (term && (term->flags & TERM_BINARY))
		f = FOPEN_BINARY(dest);
	    else
		f = fopen(dest, "w");

	    if (f == (FILE *) NULL)
		os_error(c_token, "cannot open file; output not changed");
	}
#if defined(PIPES)
	}
#endif

	term_close_output();
	gpoutfile = f;
	outstr = dest;
	opened_binary = (term && (term->flags & TERM_BINARY));
    }
}
