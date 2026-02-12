term_initialise()
{
    FPRINTF((stderr, "term_initialise()\n"));

    if (!term)
	int_error(NO_CARET, "No terminal defined");


    if (outstr && (term->flags & TERM_NO_OUTPUTFILE)) {
	if (interactive)
	    fprintf(stderr,"Closing %s\n",outstr);
	term_close_output();
    }

    if (outstr &&
	(((term->flags & TERM_BINARY) && !opened_binary) ||
	 ((!(term->flags & TERM_BINARY) && opened_binary)))) {


	char *temp = gp_alloc(strlen(outstr) + 1, "temp file string");
	if (temp) {
	    FPRINTF((stderr, "term_initialise: reopening \"%s\" as %s\n",
		     outstr, term->flags & TERM_BINARY ? "binary" : "text"));
	    strcpy(temp, outstr);
	    term_set_output(temp);
	    if (temp != outstr) {
		if (temp)
		    free(temp);
		temp = outstr;
	    }
	} else
	    fputs("Cannot reopen output file in binary", stderr);

    }
#if defined(MSDOS) || defined (_WIN32) || defined(OS2)
# ifdef _WIN32
    else if (!outstr && (term->flags & TERM_BINARY))
# else
    else if (!outstr && !interactive && (term->flags & TERM_BINARY))
# endif
	{
#if defined(_WIN32) && !defined(WGP_CONSOLE)
#ifdef PIPES
	    if (!output_pipe_open)
#endif
		if (outstr == NULL && !(term->flags & TERM_NO_OUTPUTFILE))
		    int_error(c_token, "cannot output binary data to wgnuplot text window");
#endif

	    fflush(stdout);
	    setmode(fileno(stdout), O_BINARY);
	}
#endif

    if (!term_initialised || term_force_init) {
	FPRINTF((stderr, "- calling term->init()\n"));
	(*term->init) ();
	term_initialised = TRUE;
#ifdef HAVE_LOCALE_H


	setlocale(LC_NUMERIC, "C");
#endif
    }
}
