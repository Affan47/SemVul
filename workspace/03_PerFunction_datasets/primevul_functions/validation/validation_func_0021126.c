spell_load_file(
    char_u	*fname,
    char_u	*lang,
    slang_T	*old_lp,
    int		silent)
{
    FILE	*fd;
    char_u	buf[VIMSPELLMAGICL];
    char_u	*p;
    int		i;
    int		n;
    int		len;
    char_u	*save_sourcing_name = sourcing_name;
    linenr_T	save_sourcing_lnum = sourcing_lnum;
    slang_T	*lp = NULL;
    int		c = 0;
    int		res;

    fd = mch_fopen((char *)fname, "r");
    if (fd == NULL)
    {
	if (!silent)
	    EMSG2(_(e_notopen), fname);
	else if (p_verbose > 2)
	{
	    verbose_enter();
	    smsg((char_u *)e_notopen, fname);
	    verbose_leave();
	}
	goto endFAIL;
    }
    if (p_verbose > 2)
    {
	verbose_enter();
	smsg((char_u *)_("Reading spell file \"%s\""), fname);
	verbose_leave();
    }

    if (old_lp == NULL)
    {
	lp = slang_alloc(lang);
	if (lp == NULL)
	    goto endFAIL;


	lp->sl_fname = vim_strsave(fname);
	if (lp->sl_fname == NULL)
	    goto endFAIL;


	lp->sl_add = strstr((char *)gettail(fname), SPL_FNAME_ADD) != NULL;
    }
    else
	lp = old_lp;


    sourcing_name = fname;
    sourcing_lnum = 0;


    for (i = 0; i < VIMSPELLMAGICL; ++i)
	buf[i] = getc(fd);
    if (STRNCMP(buf, VIMSPELLMAGIC, VIMSPELLMAGICL) != 0)
    {
	EMSG(_("E757: This does not look like a spell file"));
	goto endFAIL;
    }
    c = getc(fd);
    if (c < VIMSPELLVERSION)
    {
	EMSG(_("E771: Old spell file, needs to be updated"));
	goto endFAIL;
    }
    else if (c > VIMSPELLVERSION)
    {
	EMSG(_("E772: Spell file is for newer version of Vim"));
	goto endFAIL;
    }


    for (;;)
    {
	n = getc(fd);
	if (n == SN_END)
	    break;
	c = getc(fd);
	len = get4c(fd);
	if (len < 0)
	    goto truncerr;

	res = 0;
	switch (n)
	{
	    case SN_INFO:
		lp->sl_info = read_string(fd, len);
		if (lp->sl_info == NULL)
		    goto endFAIL;
		break;

	    case SN_REGION:
		res = read_region_section(fd, lp, len);
		break;

	    case SN_CHARFLAGS:
		res = read_charflags_section(fd);
		break;

	    case SN_MIDWORD:
		lp->sl_midword = read_string(fd, len);
		if (lp->sl_midword == NULL)
		    goto endFAIL;
		break;

	    case SN_PREFCOND:
		res = read_prefcond_section(fd, lp);
		break;

	    case SN_REP:
		res = read_rep_section(fd, &lp->sl_rep, lp->sl_rep_first);
		break;

	    case SN_REPSAL:
		res = read_rep_section(fd, &lp->sl_repsal, lp->sl_repsal_first);
		break;

	    case SN_SAL:
		res = read_sal_section(fd, lp);
		break;

	    case SN_SOFO:
		res = read_sofo_section(fd, lp);
		break;

	    case SN_MAP:
		p = read_string(fd, len);
		if (p == NULL)
		    goto endFAIL;
		set_map_str(lp, p);
		vim_free(p);
		break;

	    case SN_WORDS:
		res = read_words_section(fd, lp, len);
		break;

	    case SN_SUGFILE:
		lp->sl_sugtime = get8ctime(fd);
		break;

	    case SN_NOSPLITSUGS:
		lp->sl_nosplitsugs = TRUE;
		break;

	    case SN_NOCOMPOUNDSUGS:
		lp->sl_nocompoundsugs = TRUE;
		break;

	    case SN_COMPOUND:
		res = read_compound(fd, lp, len);
		break;

	    case SN_NOBREAK:
		lp->sl_nobreak = TRUE;
		break;

	    case SN_SYLLABLE:
		lp->sl_syllable = read_string(fd, len);
		if (lp->sl_syllable == NULL)
		    goto endFAIL;
		if (init_syl_tab(lp) == FAIL)
		    goto endFAIL;
		break;

	    default:


		if (c & SNF_REQUIRED)
		{
		    EMSG(_("E770: Unsupported section in spell file"));
		    goto endFAIL;
		}
		while (--len >= 0)
		    if (getc(fd) < 0)
			goto truncerr;
		break;
	}
someerror:
	if (res == SP_FORMERROR)
	{
	    EMSG(_(e_format));
	    goto endFAIL;
	}
	if (res == SP_TRUNCERROR)
	{
truncerr:
	    EMSG(_(e_spell_trunc));
	    goto endFAIL;
	}
	if (res == SP_OTHERERROR)
	    goto endFAIL;
    }


    res = spell_read_tree(fd, &lp->sl_fbyts, &lp->sl_fidxs, FALSE, 0);
    if (res != 0)
	goto someerror;


    res = spell_read_tree(fd, &lp->sl_kbyts, &lp->sl_kidxs, FALSE, 0);
    if (res != 0)
	goto someerror;


    res = spell_read_tree(fd, &lp->sl_pbyts, &lp->sl_pidxs, TRUE,
							    lp->sl_prefixcnt);
    if (res != 0)
	goto someerror;


    if (old_lp == NULL && lang != NULL)
    {
	lp->sl_next = first_lang;
	first_lang = lp;
    }

    goto endOK;

endFAIL:
    if (lang != NULL)

	*lang = NUL;
    if (lp != NULL && old_lp == NULL)
	slang_free(lp);
    lp = NULL;

endOK:
    if (fd != NULL)
	fclose(fd);
    sourcing_name = save_sourcing_name;
    sourcing_lnum = save_sourcing_lnum;

    return lp;
}
