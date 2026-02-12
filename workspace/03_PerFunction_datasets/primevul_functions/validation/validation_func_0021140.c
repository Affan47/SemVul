suggest_load_files(void)
{
    langp_T	*lp;
    int		lpi;
    slang_T	*slang;
    char_u	*dotp;
    FILE	*fd;
    char_u	buf[MAXWLEN];
    int		i;
    time_t	timestamp;
    int		wcount;
    int		wordnr;
    garray_T	ga;
    int		c;


    for (lpi = 0; lpi < curwin->w_s->b_langp.ga_len; ++lpi)
    {
	lp = LANGP_ENTRY(curwin->w_s->b_langp, lpi);
	slang = lp->lp_slang;
	if (slang->sl_sugtime != 0 && !slang->sl_sugloaded)
	{


	    slang->sl_sugloaded = TRUE;

	    dotp = vim_strrchr(slang->sl_fname, '.');
	    if (dotp == NULL || fnamecmp(dotp, ".spl") != 0)
		continue;
	    STRCPY(dotp, ".sug");
	    fd = mch_fopen((char *)slang->sl_fname, "r");
	    if (fd == NULL)
		goto nextone;


	    for (i = 0; i < VIMSUGMAGICL; ++i)
		buf[i] = getc(fd);
	    if (STRNCMP(buf, VIMSUGMAGIC, VIMSUGMAGICL) != 0)
	    {
		EMSG2(_("E778: This does not look like a .sug file: %s"),
							     slang->sl_fname);
		goto nextone;
	    }
	    c = getc(fd);
	    if (c < VIMSUGVERSION)
	    {
		EMSG2(_("E779: Old .sug file, needs to be updated: %s"),
							     slang->sl_fname);
		goto nextone;
	    }
	    else if (c > VIMSUGVERSION)
	    {
		EMSG2(_("E780: .sug file is for newer version of Vim: %s"),
							     slang->sl_fname);
		goto nextone;
	    }


	    timestamp = get8ctime(fd);
	    if (timestamp != slang->sl_sugtime)
	    {
		EMSG2(_("E781: .sug file doesn't match .spl file: %s"),
							     slang->sl_fname);
		goto nextone;
	    }


	    if (spell_read_tree(fd, &slang->sl_sbyts, &slang->sl_sidxs,
							       FALSE, 0) != 0)
	    {
someerror:
		EMSG2(_("E782: error while reading .sug file: %s"),
							     slang->sl_fname);
		slang_clear_sug(slang);
		goto nextone;
	    }


	    slang->sl_sugbuf = open_spellbuf();
	    if (slang->sl_sugbuf == NULL)
		goto someerror;

	    wcount = get4c(fd);
	    if (wcount < 0)
		goto someerror;


	    ga_init2(&ga, 1, 100);
	    for (wordnr = 0; wordnr < wcount; ++wordnr)
	    {
		ga.ga_len = 0;
		for (;;)
		{
		    c = getc(fd);
		    if (c < 0 || ga_grow(&ga, 1) == FAIL)
			goto someerror;
		    ((char_u *)ga.ga_data)[ga.ga_len++] = c;
		    if (c == NUL)
			break;
		}
		if (ml_append_buf(slang->sl_sugbuf, (linenr_T)wordnr,
					 ga.ga_data, ga.ga_len, TRUE) == FAIL)
		    goto someerror;
	    }
	    ga_clear(&ga);


	    tree_count_words(slang->sl_fbyts, slang->sl_fidxs);
	    tree_count_words(slang->sl_sbyts, slang->sl_sidxs);

nextone:
	    if (fd != NULL)
		fclose(fd);
	    STRCPY(dotp, ".spl");
	}
    }
}
