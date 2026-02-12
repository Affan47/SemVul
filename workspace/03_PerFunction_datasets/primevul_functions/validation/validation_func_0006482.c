ins_compl_files(
    int		count,
    char_u	**files,
    int		thesaurus,
    int		flags,
    regmatch_T	*regmatch,
    char_u	*buf,
    int		*dir)
{
    char_u	*ptr;
    int		i;
    FILE	*fp;
    int		add_r;

    for (i = 0; i < count && !got_int && !compl_interrupted; i++)
    {
	fp = mch_fopen((char *)files[i], "r");
	if (flags != DICT_EXACT)
	{
	    msg_hist_off = TRUE;
	    vim_snprintf((char *)IObuff, IOSIZE,
			      _("Scanning dictionary: %s"), (char *)files[i]);
	    (void)msg_trunc_attr((char *)IObuff, TRUE, HL_ATTR(HLF_R));
	}

	if (fp == NULL)
	    continue;


	while (!got_int && !compl_interrupted && !vim_fgets(buf, LSIZE, fp))
	{
	    ptr = buf;
	    while (vim_regexec(regmatch, buf, (colnr_T)(ptr - buf)))
	    {
		ptr = regmatch->startp[0];
		if (ctrl_x_mode_line_or_eval())
		    ptr = find_line_end(ptr);
		else
		    ptr = find_word_end(ptr);
		add_r = ins_compl_add_infercase(regmatch->startp[0],
			(int)(ptr - regmatch->startp[0]),
			p_ic, files[i], *dir, FALSE);
		if (thesaurus)
		{

		    ptr = buf;
		    add_r = thesarurs_add_words_in_line(files[i], &ptr, *dir,
							regmatch->startp[0]);
		}
		if (add_r == OK)

		    *dir = FORWARD;
		else if (add_r == FAIL)
		    break;


		if (*ptr == '\n' || got_int)
		    break;
	    }
	    line_breakcheck();
	    ins_compl_check_keys(50, FALSE);
	}
	fclose(fp);
    }
}
