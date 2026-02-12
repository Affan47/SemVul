handle_dcs(char_u *tp, char_u *argp, int len, char_u *key_name, int *slen)
{
    int i, j;

    j = 1 + (tp[0] == ESC);
    if (len < j + 3)
	i = len;
    else if ((argp[1] != '+' && argp[1] != '$') || argp[2] != 'r')
	i = 0;
    else if (argp[1] == '+')

	for (i = j; i < len; ++i)
	{
	    if ((tp[i] == ESC && i + 1 < len && tp[i + 1] == '\\')
		    || tp[i] == STERM)
	    {
		if (i - j >= 3)
		    got_code_from_term(tp + j, i);
		key_name[0] = (int)KS_EXTRA;
		key_name[1] = (int)KE_IGNORE;
		*slen = i + 1 + (tp[i] == ESC);
		break;
	    }
	}
    else
    {


	for (i = j + 3; i < len; ++i)
	{
	    if (i - j == 3 && !isdigit(tp[i]))
		break;
	    if (i - j == 4 && tp[i] != ' ')
		break;
	    if (i - j == 5 && tp[i] != 'q')
		break;
	    if (i - j == 6 && tp[i] != ESC && tp[i] != STERM)
		break;
	    if ((i - j == 6 && tp[i] == STERM)
	     || (i - j == 7 && tp[i] == '\\'))
	    {
		int number = argp[3] - '0';


		number = number == 0 ? 1 : number;
		initial_cursor_shape = (number + 1) / 2;


		initial_cursor_shape_blink =
				       (number & 1) ? FALSE : TRUE;
		rcs_status.tr_progress = STATUS_GOT;
		LOG_TR(("Received cursor shape response: %s", tp));

		key_name[0] = (int)KS_EXTRA;
		key_name[1] = (int)KE_IGNORE;
		*slen = i + 1;
# ifdef FEAT_EVAL
		set_vim_var_string(VV_TERMSTYLERESP, tp, *slen);
# endif
		break;
	    }
	}
    }

    if (i == len)
    {


	LOG_TR(("not enough characters for XT"));
	return FAIL;
    }
    return OK;
}
