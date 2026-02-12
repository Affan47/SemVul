set_init_1(void)
{
    char_u	*p;
    int		opt_idx;
    long_u	n;

#ifdef FEAT_LANGMAP
    langmap_init();
#endif


    p_cp = TRUE;


    if (mch_getenv((char_u *)"VIM_POSIX") != NULL)
    {
	set_string_default("cpo", (char_u *)CPO_ALL);
	set_string_default("shm", (char_u *)"A");
    }


    if (((p = mch_getenv((char_u *)"SHELL")) != NULL && *p != NUL)
#if defined(MSWIN)
	    || ((p = mch_getenv((char_u *)"COMSPEC")) != NULL && *p != NUL)
# ifdef WIN3264
	    || ((p = (char_u *)default_shell()) != NULL && *p != NUL)
# endif
#endif
	    )
	set_string_default("sh", p);

#ifdef FEAT_WILDIGN


    {
# ifdef UNIX
	static char	*(names[4]) = {"", "TMPDIR", "TEMP", "TMP"};
# else
	static char	*(names[3]) = {"TMPDIR", "TEMP", "TMP"};
# endif
	int		len;
	garray_T	ga;
	int		mustfree;

	ga_init2(&ga, 1, 100);
	for (n = 0; n < (long)(sizeof(names) / sizeof(char *)); ++n)
	{
	    mustfree = FALSE;
# ifdef UNIX
	    if (*names[n] == NUL)
		p = (char_u *)"/tmp";
	    else
# endif
		p = vim_getenv((char_u *)names[n], &mustfree);
	    if (p != NULL && *p != NUL)
	    {

		len = (int)STRLEN(p) + 3;
		if (ga_grow(&ga, len) == OK)
		{
		    if (ga.ga_len > 0)
			STRCAT(ga.ga_data, ",");
		    STRCAT(ga.ga_data, p);
		    add_pathsep(ga.ga_data);
		    STRCAT(ga.ga_data, "*");
		    ga.ga_len += len;
		}
	    }
	    if (mustfree)
		vim_free(p);
	}
	if (ga.ga_data != NULL)
	{
	    set_string_default("bsk", ga.ga_data);
	    vim_free(ga.ga_data);
	}
    }
#endif


    opt_idx = findoption((char_u *)"maxmemtot");
    if (opt_idx >= 0)
    {
#if !defined(HAVE_AVAIL_MEM) && !defined(HAVE_TOTAL_MEM)
	if (options[opt_idx].def_val[VI_DEFAULT] == (char_u *)0L)
#endif
	{
#ifdef HAVE_AVAIL_MEM

	    n = (mch_avail_mem(FALSE) >> 1);
#else
# ifdef HAVE_TOTAL_MEM

	    n = (mch_total_mem(FALSE) >> 1);
# else
	    n = (0x7fffffff >> 11);
# endif
#endif
	    options[opt_idx].def_val[VI_DEFAULT] = (char_u *)n;
	    opt_idx = findoption((char_u *)"maxmem");
	    if (opt_idx >= 0)
	    {
#if !defined(HAVE_AVAIL_MEM) && !defined(HAVE_TOTAL_MEM)
		if ((long)(long_i)options[opt_idx].def_val[VI_DEFAULT] > (long)n
		  || (long)(long_i)options[opt_idx].def_val[VI_DEFAULT] == 0L)
#endif
		    options[opt_idx].def_val[VI_DEFAULT] = (char_u *)n;
	    }
	}
    }

#ifdef FEAT_SEARCHPATH
    {
	char_u	*cdpath;
	char_u	*buf;
	int	i;
	int	j;
	int	mustfree = FALSE;


	cdpath = vim_getenv((char_u *)"CDPATH", &mustfree);
	if (cdpath != NULL)
	{
	    buf = alloc((unsigned)((STRLEN(cdpath) << 1) + 2));
	    if (buf != NULL)
	    {
		buf[0] = ',';
		j = 1;
		for (i = 0; cdpath[i] != NUL; ++i)
		{
		    if (vim_ispathlistsep(cdpath[i]))
			buf[j++] = ',';
		    else
		    {
			if (cdpath[i] == ' ' || cdpath[i] == ',')
			    buf[j++] = '\\';
			buf[j++] = cdpath[i];
		    }
		}
		buf[j] = NUL;
		opt_idx = findoption((char_u *)"cdpath");
		if (opt_idx >= 0)
		{
		    options[opt_idx].def_val[VI_DEFAULT] = buf;
		    options[opt_idx].flags |= P_DEF_ALLOCED;
		}
		else
		    vim_free(buf);
	    }
	    if (mustfree)
		vim_free(cdpath);
	}
    }
#endif

#if defined(FEAT_POSTSCRIPT) && (defined(MSWIN) || defined(VMS) || defined(EBCDIC) || defined(MAC) || defined(hpux))

    set_string_default("penc",
# if defined(MSWIN)
		       (char_u *)"cp1252"
# else
#  ifdef VMS
		       (char_u *)"dec-mcs"
#  else
#   ifdef EBCDIC
		       (char_u *)"ebcdic-uk"
#   else
#    ifdef MAC
		       (char_u *)"mac-roman"
#    else
		       (char_u *)"hp-roman8"
#    endif
#   endif
#  endif
# endif
		       );
#endif

#ifdef FEAT_POSTSCRIPT

    set_string_default("pexpr",
# if defined(MSWIN)
	    (char_u *)"system('copy' . ' ' . v:fname_in . (&printdevice == '' ? ' LPT1:' : (' \"' . &printdevice . '\"'))) . delete(v:fname_in)"
# else
#  ifdef VMS
	    (char_u *)"system('print/delete' . (&printdevice == '' ? '' : ' /queue=' . &printdevice) . ' ' . v:fname_in)"

#  else
	    (char_u *)"system('lpr' . (&printdevice == '' ? '' : ' -P' . &printdevice) . ' ' . v:fname_in) . delete(v:fname_in) + v:shell_error"
#  endif
# endif
	    );
#endif


    set_options_default(0);

#ifdef FEAT_GUI
    if (found_reverse_arg)
	set_option_value((char_u *)"bg", 0L, (char_u *)"dark", 0);
#endif

    curbuf->b_p_initialized = TRUE;
    curbuf->b_p_ar = -1;
    curbuf->b_p_ul = NO_LOCAL_UNDOLEVEL;
    check_buf_options(curbuf);
    check_win_options(curwin);
    check_options();


    didset_options();

#ifdef FEAT_SPELL


    init_spell_chartab();
#endif


    for (opt_idx = 0; !istermoption(&options[opt_idx]); opt_idx++)
    {
	if ((options[opt_idx].flags & P_GETTEXT)
					      && options[opt_idx].var != NULL)
	    p = (char_u *)_(*(char **)options[opt_idx].var);
	else
	    p = option_expand(opt_idx, NULL);
	if (p != NULL && (p = vim_strsave(p)) != NULL)
	{
	    *(char_u **)options[opt_idx].var = p;


	    if (options[opt_idx].flags & P_DEF_ALLOCED)
		vim_free(options[opt_idx].def_val[VI_DEFAULT]);
	    options[opt_idx].def_val[VI_DEFAULT] = p;
	    options[opt_idx].flags |= P_DEF_ALLOCED;
	}
    }

    save_file_ff(curbuf);

#if defined(FEAT_ARABIC)


    if (mch_getenv((char_u *)"MLTERM") != NULL)
	set_option_value((char_u *)"tbidi", 1L, NULL, 0);
#endif

    didset_options2();

#ifdef FEAT_MBYTE
# if defined(WIN3264) && defined(FEAT_GETTEXT)


    if (mch_getenv((char_u *)"LANG") == NULL)
    {
	char	buf[20];


	n = GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SABBREVLANGNAME,
							     (LPTSTR)buf, 20);
	if (n >= 2 && STRNICMP(buf, "en", 2) != 0)
	{

	    if (STRNICMP(buf, "cht", 3) == 0 || STRNICMP(buf, "zht", 3) == 0)
		STRCPY(buf, "zh_TW");
	    else if (STRNICMP(buf, "chs", 3) == 0
					      || STRNICMP(buf, "zhc", 3) == 0)
		STRCPY(buf, "zh_CN");
	    else if (STRNICMP(buf, "jp", 2) == 0)
		STRCPY(buf, "ja");
	    else
		buf[2] = NUL;
	    vim_setenv((char_u *)"LANG", (char_u *)buf);
	}
    }
# else
#  ifdef MACOS_CONVERT

    mac_lang_init();
#  endif
# endif


    p = enc_locale();
    if (p != NULL)
    {
	char_u *save_enc;


	save_enc = p_enc;
	p_enc = p;
	if (STRCMP(p_enc, "gb18030") == 0)
	{


	    p_enc = vim_strsave((char_u *)"cp936");
	    vim_free(p);
	}
	if (mb_init() == NULL)
	{
	    opt_idx = findoption((char_u *)"encoding");
	    if (opt_idx >= 0)
	    {
		options[opt_idx].def_val[VI_DEFAULT] = p_enc;
		options[opt_idx].flags |= P_DEF_ALLOCED;
	    }

#if defined(MSWIN) || defined(MACOS) || defined(VMS)
	    if (STRCMP(p_enc, "latin1") == 0
# ifdef FEAT_MBYTE
		    || enc_utf8
# endif
		    )
	    {


		set_string_option_direct((char_u *)"isp", -1,
					      ISP_LATIN1, OPT_FREE, SID_NONE);
		set_string_option_direct((char_u *)"isk", -1,
					      ISK_LATIN1, OPT_FREE, SID_NONE);
		opt_idx = findoption((char_u *)"isp");
		if (opt_idx >= 0)
		    options[opt_idx].def_val[VIM_DEFAULT] = ISP_LATIN1;
		opt_idx = findoption((char_u *)"isk");
		if (opt_idx >= 0)
		    options[opt_idx].def_val[VIM_DEFAULT] = ISK_LATIN1;
		(void)init_chartab();
	    }
#endif

# if defined(WIN3264) && !defined(FEAT_GUI)


	    if (GetACP() != GetConsoleCP())
	    {
		char	buf[50];

		sprintf(buf, "cp%ld", (long)GetConsoleCP());
		p_tenc = vim_strsave((char_u *)buf);
		if (p_tenc != NULL)
		{
		    opt_idx = findoption((char_u *)"termencoding");
		    if (opt_idx >= 0)
		    {
			options[opt_idx].def_val[VI_DEFAULT] = p_tenc;
			options[opt_idx].flags |= P_DEF_ALLOCED;
		    }
		    convert_setup(&input_conv, p_tenc, p_enc);
		    convert_setup(&output_conv, p_enc, p_tenc);
		}
		else
		    p_tenc = empty_option;
	    }
# endif
# if defined(WIN3264) && defined(FEAT_MBYTE)

	    init_homedir();
# endif
	}
	else
	{
	    vim_free(p_enc);
	    p_enc = save_enc;
	}
    }
#endif

#ifdef FEAT_MULTI_LANG

    set_helplang_default(get_mess_lang());
#endif
}
