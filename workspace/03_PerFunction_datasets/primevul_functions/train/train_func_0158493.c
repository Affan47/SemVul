prepare_help_buffer(void)
{
    char_u	*p;

    curbuf->b_help = TRUE;
#ifdef FEAT_QUICKFIX
    set_string_option_direct((char_u *)"buftype", -1,
				     (char_u *)"help", OPT_FREE|OPT_LOCAL, 0);
#endif


    p =
#ifdef EBCDIC
	    (char_u *)"65-255,^*,^|,^\"";
#else
	    (char_u *)"!-~,^*,^|,^\",192-255";
#endif
    if (STRCMP(curbuf->b_p_isk, p) != 0)
    {
	set_string_option_direct((char_u *)"isk", -1, p, OPT_FREE|OPT_LOCAL, 0);
	check_buf_options(curbuf);
	(void)buf_init_chartab(curbuf, FALSE);
    }

#ifdef FEAT_FOLDING

    set_string_option_direct((char_u *)"fdm", -1, (char_u *)"manual",
						       OPT_FREE|OPT_LOCAL, 0);
#endif

    curbuf->b_p_ts = 8;
    curwin->w_p_list = FALSE;

    curbuf->b_p_ma = FALSE;
    curbuf->b_p_bin = FALSE;
    curwin->w_p_nu = 0;
    curwin->w_p_rnu = 0;
    RESET_BINDING(curwin);
#ifdef FEAT_ARABIC
    curwin->w_p_arab = FALSE;
#endif
#ifdef FEAT_RIGHTLEFT
    curwin->w_p_rl  = FALSE;
#endif
#ifdef FEAT_FOLDING
    curwin->w_p_fen = FALSE;
#endif
#ifdef FEAT_DIFF
    curwin->w_p_diff = FALSE;
#endif
#ifdef FEAT_SPELL
    curwin->w_p_spell = FALSE;
#endif

    set_buflisted(FALSE);
}
