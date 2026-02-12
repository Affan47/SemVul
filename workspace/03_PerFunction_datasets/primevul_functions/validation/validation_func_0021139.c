spell_make_sugfile(spellinfo_T *spin, char_u *wfname)
{
    char_u	*fname = NULL;
    int		len;
    slang_T	*slang;
    int		free_slang = FALSE;


    for (slang = first_lang; slang != NULL; slang = slang->sl_next)
	if (fullpathcmp(wfname, slang->sl_fname, FALSE) == FPC_SAME)
	    break;
    if (slang == NULL)
    {
	spell_message(spin, (char_u *)_("Reading back spell file..."));
	slang = spell_load_file(wfname, NULL, NULL, FALSE);
	if (slang == NULL)
	    return;
	free_slang = TRUE;
    }


    spin->si_blocks = NULL;
    spin->si_blocks_cnt = 0;
    spin->si_compress_cnt = 0;
    spin->si_free_count = 0;
    spin->si_first_free = NULL;
    spin->si_foldwcount = 0;


    spell_message(spin, (char_u *)_("Performing soundfolding..."));
    if (sug_filltree(spin, slang) == FAIL)
	goto theend;


    if (sug_maketable(spin) == FAIL)
	goto theend;

    smsg((char_u *)_("Number of words after soundfolding: %ld"),
				 (long)spin->si_spellbuf->b_ml.ml_line_count);


    spell_message(spin, (char_u *)_(msg_compressing));
    wordtree_compress(spin, spin->si_foldroot);


    fname = alloc(MAXPATHL);
    if (fname == NULL)
	goto theend;
    vim_strncpy(fname, wfname, MAXPATHL - 1);
    len = (int)STRLEN(fname);
    fname[len - 2] = 'u';
    fname[len - 1] = 'g';
    sug_write(spin, fname);

theend:
    vim_free(fname);
    if (free_slang)
	slang_free(slang);
    free_blocks(spin->si_blocks);
    close_spellbuf(spin->si_spellbuf);
}
