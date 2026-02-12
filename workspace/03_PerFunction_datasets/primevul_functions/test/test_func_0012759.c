separate_nextcmd(exarg_T *eap, int keep_backslash)
{
    char_u	*p;

#ifdef FEAT_QUICKFIX
    p = skip_grep_pat(eap);
#else
    p = eap->arg;
#endif

    for ( ; *p; MB_PTR_ADV(p))
    {
	if (*p == Ctrl_V)
	{
	    if ((eap->argt & (EX_CTRLV | EX_XFILE)) || keep_backslash)
		++p;
	    else

		STRMOVE(p, p + 1);
	    if (*p == NUL)
		break;
	}

#ifdef FEAT_EVAL

	else if (p[0] == '`' && p[1] == '=' && (eap->argt & EX_XFILE))
	{
	    p += 2;
	    (void)skip_expr(&p, NULL);
	    if (*p == NUL)
		break;
	}
#endif


	else if ((*p == '"'
#ifdef FEAT_EVAL
		    && !in_vim9script()
#endif
		    && !(eap->argt & EX_NOTRLCOM)
		    && ((eap->cmdidx != CMD_at && eap->cmdidx != CMD_star)
							      || p != eap->arg)
		    && (eap->cmdidx != CMD_redir
					 || p != eap->arg + 1 || p[-1] != '@'))
#ifdef FEAT_EVAL
		|| (*p == '#'
		    && in_vim9script()
		    && !(eap->argt & EX_NOTRLCOM)
		    && p > eap->cmd && VIM_ISWHITE(p[-1]))
#endif
		|| *p == '|' || *p == '\n')
	{


	    if ((vim_strchr(p_cpo, CPO_BAR) == NULL
			      || !(eap->argt & EX_CTRLV)) && *(p - 1) == '\\')
	    {
		if (!keep_backslash)
		{
		    STRMOVE(p - 1, p);
		    --p;
		}
	    }
	    else
	    {
		eap->nextcmd = check_nextcmd(p);
		*p = NUL;
		break;
	    }
	}
    }

    if (!(eap->argt & EX_NOTRLCOM))
	del_trailing_spaces(eap->arg);
}
