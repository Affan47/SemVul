getcmdkeycmd(
	int		promptc UNUSED,
	void		*cookie UNUSED,
	int		indent UNUSED,
	getline_opt_T	do_concat UNUSED)
{
    garray_T	line_ga;
    int		c1 = -1;
    int		c2;
    int		cmod = 0;
    int		aborted = FALSE;

    ga_init2(&line_ga, 1, 32);


    no_mapping++;

    got_int = FALSE;
    while (c1 != NUL && !aborted)
    {
	if (ga_grow(&line_ga, 32) != OK)
	{
	    aborted = TRUE;
	    break;
	}

	if (vgetorpeek(FALSE) == NUL)
	{


	    emsg(_(e_cmd_mapping_must_end_with_cr));
	    aborted = TRUE;
	    break;
	}


	c1 = vgetorpeek(TRUE);


	if (c1 == K_SPECIAL)
	{
	    c1 = vgetorpeek(TRUE);
	    c2 = vgetorpeek(TRUE);
	    if (c1 == KS_MODIFIER)
	    {
		cmod = c2;
		continue;
	    }
	    c1 = TO_SPECIAL(c1, c2);
	}
	if (c1 == Ctrl_V)
	{


	    no_reduce_keys = TRUE;
	    c1 = get_literal(TRUE);
	    no_reduce_keys = FALSE;
	}

	if (got_int)
	    aborted = TRUE;
	else if (c1 == '\r' || c1 == '\n')
	    c1 = NUL;
	else if (c1 == ESC)
	    aborted = TRUE;
	else if (c1 == K_COMMAND || c1 == K_SCRIPT_COMMAND)
	{

	    emsg(_(e_cmd_mapping_must_end_with_cr_before_second_cmd));
	    aborted = TRUE;
	}
	else if (IS_SPECIAL(c1))
	{
	    if (c1 == K_SNR)
		ga_concat(&line_ga, (char_u *)"<SNR>");
	    else
	    {
		semsg(e_cmd_maping_must_not_include_str_key,
					       get_special_key_name(c1, cmod));
		aborted = TRUE;
	    }
	}
	else
	    ga_append(&line_ga, c1);

	cmod = 0;
    }

    no_mapping--;

    if (aborted)
	ga_clear(&line_ga);

    return (char_u *)line_ga.ga_data;
}
