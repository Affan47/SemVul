fix_help_buffer(void)
{
    linenr_T	lnum;
    char_u	*line;
    int		in_example = FALSE;
    int		len;
    char_u	*fname;
    char_u	*p;
    char_u	*rt;
    int		mustfree;


    if (STRCMP(curbuf->b_p_ft, "help") != 0)
    {
	++curbuf_lock;
	set_option_value((char_u *)"ft", 0L, (char_u *)"help", OPT_LOCAL);
	--curbuf_lock;
    }

#ifdef FEAT_SYN_HL
    if (!syntax_present(curwin))
#endif
    {
	for (lnum = 1; lnum <= curbuf->b_ml.ml_line_count; ++lnum)
	{
	    line = ml_get_buf(curbuf, lnum, FALSE);
	    len = (int)STRLEN(line);
	    if (in_example && len > 0 && !VIM_ISWHITE(line[0]))
	    {

		if (line[0] == '<')
		{

		    line = ml_get_buf(curbuf, lnum, TRUE);
		    line[0] = ' ';
		}
		in_example = FALSE;
	    }
	    if (!in_example && len > 0)
	    {
		if (line[len - 1] == '>' && (len == 1 || line[len - 2] == ' '))
		{

		    line = ml_get_buf(curbuf, lnum, TRUE);
		    line[len - 1] = ' ';
		    in_example = TRUE;
		}
		else if (line[len - 1] == '~')
		{

		    line = ml_get_buf(curbuf, lnum, TRUE);
		    line[len - 1] = ' ';
		}
	    }
	}
    }


    fname = gettail(curbuf->b_fname);
    if (fnamecmp(fname, "help.txt") == 0
#ifdef FEAT_MULTI_LANG
	|| (fnamencmp(fname, "help.", 5) == 0
	    && ASCII_ISALPHA(fname[5])
	    && ASCII_ISALPHA(fname[6])
	    && TOLOWER_ASC(fname[7]) == 'x'
	    && fname[8] == NUL)
#endif
	)
    {
	for (lnum = 1; lnum < curbuf->b_ml.ml_line_count; ++lnum)
	{
	    line = ml_get_buf(curbuf, lnum, FALSE);
	    if (strstr((char *)line, "*local-additions*") == NULL)
		continue;


	    p = p_rtp;
	    while (*p != NUL)
	    {
		copy_option_part(&p, NameBuff, MAXPATHL, ",");
		mustfree = FALSE;
		rt = vim_getenv((char_u *)"VIMRUNTIME", &mustfree);
		if (rt != NULL &&
			    fullpathcmp(rt, NameBuff, FALSE, TRUE) != FPC_SAME)
		{
		    int		fcount;
		    char_u	**fnames;
		    FILE	*fd;
		    char_u	*s;
		    int		fi;
		    vimconv_T	vc;
		    char_u	*cp;


		    add_pathsep(NameBuff);
#ifdef FEAT_MULTI_LANG
		    STRCAT(NameBuff, "doc/*.??[tx]");
#else
		    STRCAT(NameBuff, "doc/*.txt");
#endif
		    if (gen_expand_wildcards(1, &NameBuff, &fcount,
					 &fnames, EW_FILE|EW_SILENT) == OK
			    && fcount > 0)
		    {
#ifdef FEAT_MULTI_LANG
			int	i1, i2;
			char_u	*f1, *f2;
			char_u	*t1, *t2;
			char_u	*e1, *e2;


			for (i1 = 0; i1 < fcount; ++i1)
			{
			    for (i2 = 0; i2 < fcount; ++i2)
			    {
				if (i1 == i2)
				    continue;
				if (fnames[i1] == NULL || fnames[i2] == NULL)
				    continue;
				f1 = fnames[i1];
				f2 = fnames[i2];
				t1 = gettail(f1);
				t2 = gettail(f2);
				e1 = vim_strrchr(t1, '.');
				e2 = vim_strrchr(t2, '.');
				if (e1 == NULL || e2 == NULL)
				    continue;
				if (fnamecmp(e1, ".txt") != 0
				    && fnamecmp(e1, fname + 4) != 0)
				{

				    VIM_CLEAR(fnames[i1]);
				    continue;
				}
				if (e1 - f1 != e2 - f2
					    || fnamencmp(f1, f2, e1 - f1) != 0)
				    continue;
				if (fnamecmp(e1, ".txt") == 0
				    && fnamecmp(e2, fname + 4) == 0)

				    VIM_CLEAR(fnames[i1]);
			    }
			}
#endif
			for (fi = 0; fi < fcount; ++fi)
			{
			    if (fnames[fi] == NULL)
				continue;
			    fd = mch_fopen((char *)fnames[fi], "r");
			    if (fd != NULL)
			    {
				vim_fgets(IObuff, IOSIZE, fd);
				if (IObuff[0] == '*'
					&& (s = vim_strchr(IObuff + 1, '*'))
								  != NULL)
				{
				    int	this_utf = MAYBE;


				    IObuff[0] = '|';
				    *s = '|';
				    while (*s != NUL)
				    {
					if (*s == '\r' || *s == '\n')
					    *s = NUL;


					if (*s >= 0x80 && this_utf != FALSE)
					{
					    int	l;

					    this_utf = TRUE;
					    l = utf_ptr2len(s);
					    if (l == 1)
						this_utf = FALSE;
					    s += l - 1;
					}
					++s;
				    }


				    vc.vc_type = CONV_NONE;
				    convert_setup(&vc, (char_u *)(
						this_utf == TRUE ? "utf-8"
						      : "latin1"), p_enc);
				    if (vc.vc_type == CONV_NONE)

					cp = IObuff;
				    else
				    {


					cp = string_convert(&vc, IObuff,
								    NULL);
					if (cp == NULL)
					    cp = IObuff;
				    }
				    convert_setup(&vc, NULL, NULL);

				    ml_append(lnum, cp, (colnr_T)0, FALSE);
				    if (cp != IObuff)
					vim_free(cp);
				    ++lnum;
				}
				fclose(fd);
			    }
			}
			FreeWild(fcount, fnames);
		    }
		}
		if (mustfree)
		    vim_free(rt);
	    }
	    break;
	}
    }
}
