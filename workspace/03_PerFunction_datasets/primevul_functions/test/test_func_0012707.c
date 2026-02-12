nfa_regatom(void)
{
    int		c;
    int		charclass;
    int		equiclass;
    int		collclass;
    int		got_coll_char;
    char_u	*p;
    char_u	*endp;
    char_u	*old_regparse = regparse;
    int		extra = 0;
    int		emit_range;
    int		negated;
    int		result;
    int		startc = -1;
    int		save_prev_at_start = prev_at_start;

    c = getchr();
    switch (c)
    {
	case NUL:
	    EMSG_RET_FAIL(_(e_nul_found));

	case Magic('^'):
	    EMIT(NFA_BOL);
	    break;

	case Magic('$'):
	    EMIT(NFA_EOL);
#if defined(FEAT_SYN_HL) || defined(PROTO)
	    had_eol = TRUE;
#endif
	    break;

	case Magic('<'):
	    EMIT(NFA_BOW);
	    break;

	case Magic('>'):
	    EMIT(NFA_EOW);
	    break;

	case Magic('_'):
	    c = no_Magic(getchr());
	    if (c == NUL)
		EMSG_RET_FAIL(_(e_nul_found));

	    if (c == '^')
	    {
		EMIT(NFA_BOL);
		break;
	    }
	    if (c == '$')
	    {
		EMIT(NFA_EOL);
#if defined(FEAT_SYN_HL) || defined(PROTO)
		had_eol = TRUE;
#endif
		break;
	    }

	    extra = NFA_ADD_NL;

	    if (c == '[')
		goto collection;

	case Magic('.'):
	case Magic('i'):
	case Magic('I'):
	case Magic('k'):
	case Magic('K'):
	case Magic('f'):
	case Magic('F'):
	case Magic('p'):
	case Magic('P'):
	case Magic('s'):
	case Magic('S'):
	case Magic('d'):
	case Magic('D'):
	case Magic('x'):
	case Magic('X'):
	case Magic('o'):
	case Magic('O'):
	case Magic('w'):
	case Magic('W'):
	case Magic('h'):
	case Magic('H'):
	case Magic('a'):
	case Magic('A'):
	case Magic('l'):
	case Magic('L'):
	case Magic('u'):
	case Magic('U'):
	    p = vim_strchr(classchars, no_Magic(c));
	    if (p == NULL)
	    {
		if (extra == NFA_ADD_NL)
		{
		    semsg(_(e_ill_char_class), c);
		    rc_did_emsg = TRUE;
		    return FAIL;
		}
		siemsg("INTERNAL: Unknown character class char: %d", c);
		return FAIL;
	    }

	    if (enc_utf8 && c == Magic('.') && utf_iscomposing(peekchr()))
	    {
		old_regparse = regparse;
		c = getchr();
		goto nfa_do_multibyte;
	    }
	    EMIT(nfa_classcodes[p - classchars]);
	    if (extra == NFA_ADD_NL)
	    {
		EMIT(NFA_NEWL);
		EMIT(NFA_OR);
		regflags |= RF_HASNL;
	    }
	    break;

	case Magic('n'):
	    if (reg_string)

		EMIT(NL);
	    else
	    {

		EMIT(NFA_NEWL);
		regflags |= RF_HASNL;
	    }
	    break;

	case Magic('('):
	    if (nfa_reg(REG_PAREN) == FAIL)
		return FAIL;
	    break;

	case Magic('|'):
	case Magic('&'):
	case Magic(')'):
	    semsg(_(e_misplaced), no_Magic(c));
	    return FAIL;

	case Magic('='):
	case Magic('?'):
	case Magic('+'):
	case Magic('@'):
	case Magic('*'):
	case Magic('{'):

	    semsg(_(e_misplaced), no_Magic(c));
	    return FAIL;

	case Magic('~'):
	    {
		char_u	    *lp;

		if (reg_prev_sub == NULL)
		{
		    emsg(_(e_no_previous_substitute_regular_expression));
		    return FAIL;
		}
		for (lp = reg_prev_sub; *lp != NUL; MB_CPTR_ADV(lp))
		{
		    EMIT(PTR2CHAR(lp));
		    if (lp != reg_prev_sub)
			EMIT(NFA_CONCAT);
		}
		EMIT(NFA_NOPEN);
		break;
	    }

	case Magic('1'):
	case Magic('2'):
	case Magic('3'):
	case Magic('4'):
	case Magic('5'):
	case Magic('6'):
	case Magic('7'):
	case Magic('8'):
	case Magic('9'):
	    {
		int refnum = no_Magic(c) - '1';

		if (!seen_endbrace(refnum + 1))
		    return FAIL;
		EMIT(NFA_BACKREF1 + refnum);
		rex.nfa_has_backref = TRUE;
	    }
	    break;

	case Magic('z'):
	    c = no_Magic(getchr());
	    switch (c)
	    {
		case 's':
		    EMIT(NFA_ZSTART);
		    if (re_mult_next("\\zs") == FAIL)
			return FAIL;
		    break;
		case 'e':
		    EMIT(NFA_ZEND);
		    rex.nfa_has_zend = TRUE;
		    if (re_mult_next("\\ze") == FAIL)
			return FAIL;
		    break;
#ifdef FEAT_SYN_HL
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':

		    if ((reg_do_extmatch & REX_USE) == 0)
			EMSG_RET_FAIL(_(e_z1_not_allowed));
		    EMIT(NFA_ZREF1 + (no_Magic(c) - '1'));

		    re_has_z = REX_USE;
		    break;
		case '(':

		    if ((reg_do_extmatch & REX_SET) == 0)
			EMSG_RET_FAIL(_(e_z_not_allowed));
		    if (nfa_reg(REG_ZPAREN) == FAIL)
			return FAIL;
		    re_has_z = REX_SET;
		    break;
#endif
		default:
		    semsg(_("E867: (NFA) Unknown operator '\\z%c'"),
								 no_Magic(c));
		    return FAIL;
	    }
	    break;

	case Magic('%'):
	    c = no_Magic(getchr());
	    switch (c)
	    {

		case '(':
		    if (nfa_reg(REG_NPAREN) == FAIL)
			return FAIL;
		    EMIT(NFA_NOPEN);
		    break;

		case 'd':
		case 'o':
		case 'x':
		case 'u':
		case 'U':
		    {
			long nr;

			switch (c)
			{
			    case 'd': nr = getdecchrs(); break;
			    case 'o': nr = getoctchrs(); break;
			    case 'x': nr = gethexchrs(2); break;
			    case 'u': nr = gethexchrs(4); break;
			    case 'U': nr = gethexchrs(8); break;
			    default:  nr = -1; break;
			}

			if (nr < 0 || nr > INT_MAX)
			    EMSG2_RET_FAIL(
			       _("E678: Invalid character after %s%%[dxouU]"),
				    reg_magic == MAGIC_ALL);

			EMIT(nr == 0 ? 0x0a : nr);
		    }
		    break;

		case '^':
		    EMIT(NFA_BOF);
		    break;

		case '$':
		    EMIT(NFA_EOF);
		    break;

		case '#':
		    EMIT(NFA_CURSOR);
		    break;

		case 'V':
		    EMIT(NFA_VISUAL);
		    break;

		case 'C':
		    EMIT(NFA_ANY_COMPOSING);
		    break;

		case '[':
		    {
			int	    n;

			for (n = 0; (c = peekchr()) != ']'; ++n)
			{
			    if (c == NUL)
				EMSG2_RET_FAIL(_(e_missing_sb),
						      reg_magic == MAGIC_ALL);

			    if (nfa_regatom() == FAIL)
				return FAIL;
			}
			getchr();
			if (n == 0)
			    EMSG2_RET_FAIL(_(e_empty_sb),
						      reg_magic == MAGIC_ALL);
			EMIT(NFA_OPT_CHARS);
			EMIT(n);

			EMIT(NFA_NOPEN);
			break;
		    }

		default:
		    {
			long_u	n = 0;
			int	cmp = c;
			int	cur = FALSE;

			if (c == '<' || c == '>')
			    c = getchr();
			if (no_Magic(c) == '.')
			{
			    cur = TRUE;
			    c = getchr();
			}
			while (VIM_ISDIGIT(c))
			{
			    long_u tmp;

			    if (cur)
				semsg(_(e_regexp_number_after_dot_pos_search),
								 no_Magic(c));
			    tmp = n * 10 + (c - '0');

			    if (tmp < n)
			    {

				emsg(_(e_value_too_large));
				return FAIL;
			    }
			    n = tmp;
			    c = getchr();
			}
			if (c == 'l' || c == 'c' || c == 'v')
			{
			    long_u limit = INT_MAX;

			    if (c == 'l')
			    {
				if (cur)
				    n = curwin->w_cursor.lnum;

				EMIT(cmp == '<' ? NFA_LNUM_LT :
				     cmp == '>' ? NFA_LNUM_GT : NFA_LNUM);
				if (save_prev_at_start)
				    at_start = TRUE;
			    }
			    else if (c == 'c')
			    {
				if (cur)
				{
				    n = curwin->w_cursor.col;
				    n++;
				}

				EMIT(cmp == '<' ? NFA_COL_LT :
				     cmp == '>' ? NFA_COL_GT : NFA_COL);
			    }
			    else
			    {
				if (cur)
				{
				    colnr_T vcol = 0;

				    getvvcol(curwin, &curwin->w_cursor,
							    NULL, NULL, &vcol);
				    n = ++vcol;
				}

				EMIT(cmp == '<' ? NFA_VCOL_LT :
				     cmp == '>' ? NFA_VCOL_GT : NFA_VCOL);
				limit = INT_MAX / MB_MAXBYTES;
			    }
			    if (n >= limit)
			    {
				emsg(_(e_value_too_large));
				return FAIL;
			    }
			    EMIT((int)n);
			    break;
			}
			else if (c == '\'' && n == 0)
			{

			    EMIT(cmp == '<' ? NFA_MARK_LT :
				 cmp == '>' ? NFA_MARK_GT : NFA_MARK);
			    EMIT(getchr());
			    break;
			}
		    }
		    semsg(_("E867: (NFA) Unknown operator '\\%%%c'"),
								 no_Magic(c));
		    return FAIL;
	    }
	    break;

	case Magic('['):
collection:

	    p = regparse;
	    endp = skip_anyof(p);
	    if (*endp == ']')
	    {

		result = nfa_recognize_char_class(regparse, endp,
							 extra == NFA_ADD_NL);
		if (result != FAIL)
		{
		    if (result >= NFA_FIRST_NL && result <= NFA_LAST_NL)
		    {
			EMIT(result - NFA_ADD_NL);
			EMIT(NFA_NEWL);
			EMIT(NFA_OR);
		    }
		    else
			EMIT(result);
		    regparse = endp;
		    MB_PTR_ADV(regparse);
		    return OK;
		}

		startc = -1;
		negated = FALSE;
		if (*regparse == '^')
		{
		    negated = TRUE;
		    MB_PTR_ADV(regparse);
		    EMIT(NFA_START_NEG_COLL);
		}
		else
		    EMIT(NFA_START_COLL);
		if (*regparse == '-')
		{
		    startc = '-';
		    EMIT(startc);
		    EMIT(NFA_CONCAT);
		    MB_PTR_ADV(regparse);
		}

		emit_range = FALSE;
		while (regparse < endp)
		{
		    int	    oldstartc = startc;

		    startc = -1;
		    got_coll_char = FALSE;
		    if (*regparse == '[')
		    {

			equiclass = collclass = 0;
			charclass = get_char_class(&regparse);
			if (charclass == CLASS_NONE)
			{
			    equiclass = get_equi_class(&regparse);
			    if (equiclass == 0)
				collclass = get_coll_element(&regparse);
			}

			if (charclass != CLASS_NONE)
			{
			    switch (charclass)
			    {
				case CLASS_ALNUM:
				    EMIT(NFA_CLASS_ALNUM);
				    break;
				case CLASS_ALPHA:
				    EMIT(NFA_CLASS_ALPHA);
				    break;
				case CLASS_BLANK:
				    EMIT(NFA_CLASS_BLANK);
				    break;
				case CLASS_CNTRL:
				    EMIT(NFA_CLASS_CNTRL);
				    break;
				case CLASS_DIGIT:
				    EMIT(NFA_CLASS_DIGIT);
				    break;
				case CLASS_GRAPH:
				    EMIT(NFA_CLASS_GRAPH);
				    break;
				case CLASS_LOWER:
				    wants_nfa = TRUE;
				    EMIT(NFA_CLASS_LOWER);
				    break;
				case CLASS_PRINT:
				    EMIT(NFA_CLASS_PRINT);
				    break;
				case CLASS_PUNCT:
				    EMIT(NFA_CLASS_PUNCT);
				    break;
				case CLASS_SPACE:
				    EMIT(NFA_CLASS_SPACE);
				    break;
				case CLASS_UPPER:
				    wants_nfa = TRUE;
				    EMIT(NFA_CLASS_UPPER);
				    break;
				case CLASS_XDIGIT:
				    EMIT(NFA_CLASS_XDIGIT);
				    break;
				case CLASS_TAB:
				    EMIT(NFA_CLASS_TAB);
				    break;
				case CLASS_RETURN:
				    EMIT(NFA_CLASS_RETURN);
				    break;
				case CLASS_BACKSPACE:
				    EMIT(NFA_CLASS_BACKSPACE);
				    break;
				case CLASS_ESCAPE:
				    EMIT(NFA_CLASS_ESCAPE);
				    break;
				case CLASS_IDENT:
				    EMIT(NFA_CLASS_IDENT);
				    break;
				case CLASS_KEYWORD:
				    EMIT(NFA_CLASS_KEYWORD);
				    break;
				case CLASS_FNAME:
				    EMIT(NFA_CLASS_FNAME);
				    break;
			    }
			    EMIT(NFA_CONCAT);
			    continue;
			}

			if (equiclass != 0)
			{
			    result = nfa_emit_equi_class(equiclass);
			    if (result == FAIL)
			    {

				EMSG_RET_FAIL(_("E868: Error building NFA with equivalence class!"));
			    }
			    continue;
			}

			if (collclass != 0)
			{
			    startc = collclass;

			}
		    }

		    if (*regparse == '-' && oldstartc != -1)
		    {
			emit_range = TRUE;
			startc = oldstartc;
			MB_PTR_ADV(regparse);
			continue;
		    }

		    if (*regparse == '\\'
			    && !reg_cpo_bsl
			    && regparse + 1 <= endp
			    && (vim_strchr(REGEXP_INRANGE, regparse[1]) != NULL
				|| (!reg_cpo_lit
				    && vim_strchr(REGEXP_ABBR, regparse[1])
								      != NULL)
			    )
			)
		    {
			MB_PTR_ADV(regparse);

			if (*regparse == 'n')
			    startc = (reg_string || emit_range
					|| regparse[1] == '-') ? NL : NFA_NEWL;
			else if (*regparse == 'd'
				    || *regparse == 'o'
				    || *regparse == 'x'
				    || *regparse == 'u'
				    || *regparse == 'U'
				)
			    {

				startc = coll_get_char();
				got_coll_char = TRUE;
				MB_PTR_BACK(old_regparse, regparse);
			    }
			    else
			    {

				startc = backslash_trans(*regparse);
			    }
		    }

		    if (startc == -1)
			startc = PTR2CHAR(regparse);

		    if (emit_range)
		    {
			int	endc = startc;

			startc = oldstartc;
			if (startc > endc)
			    EMSG_RET_FAIL(_(e_reverse_range));

			if (endc > startc + 2)
			{

			    if (startc == 0)

				EMIT(1);
			    else
				--post_ptr;
			    EMIT(endc);
			    EMIT(NFA_RANGE);
			    EMIT(NFA_CONCAT);
			}
			else if (has_mbyte && ((*mb_char2len)(startc) > 1
				    || (*mb_char2len)(endc) > 1))
			{

			    for (c = startc + 1; c <= endc; c++)
			    {
				EMIT(c);
				EMIT(NFA_CONCAT);
			    }
			}
			else
			{
#ifdef EBCDIC
			    int alpha_only = FALSE;

			    if (isalpha(startc) && isalpha(endc))
				alpha_only = TRUE;
#endif

			    for (c = startc + 1; c <= endc; c++)
#ifdef EBCDIC
				if (!alpha_only || isalpha(startc))
#endif
				{
				    EMIT(c);
				    EMIT(NFA_CONCAT);
				}
			}
			emit_range = FALSE;
			startc = -1;
		    }
		    else
		    {

			if (startc == NFA_NEWL)
			{

			    if (!negated)
				extra = NFA_ADD_NL;
			}
			else
			{
			    if (got_coll_char == TRUE && startc == 0)
				EMIT(0x0a);
			    else
				EMIT(startc);
			    EMIT(NFA_CONCAT);
			}
		    }

		    MB_PTR_ADV(regparse);
		}

		MB_PTR_BACK(old_regparse, regparse);
		if (*regparse == '-')
		{
		    EMIT('-');
		    EMIT(NFA_CONCAT);
		}

		regparse = endp;
		MB_PTR_ADV(regparse);

		if (negated == TRUE)
		    EMIT(NFA_END_NEG_COLL);
		else
		    EMIT(NFA_END_COLL);

		if (extra == NFA_ADD_NL)
		{
		    EMIT(reg_string ? NL : NFA_NEWL);
		    EMIT(NFA_OR);
		}

		return OK;
	    }

	    if (reg_strict)
		EMSG_RET_FAIL(_(e_missingbracket));

	default:
	    {
		int	plen;

nfa_do_multibyte:

		if (enc_utf8 && ((*mb_char2len)(c)
			    != (plen = utfc_ptr2len(old_regparse))
						       || utf_iscomposing(c)))
		{
		    int i = 0;

		    for (;;)
		    {
			EMIT(c);
			if (i > 0)
			    EMIT(NFA_CONCAT);
			if ((i += utf_char2len(c)) >= plen)
			    break;
			c = utf_ptr2char(old_regparse + i);
		    }
		    EMIT(NFA_COMPOSING);
		    regparse = old_regparse + plen;
		}
		else
		{
		    c = no_Magic(c);
		    EMIT(c);
		}
		return OK;
	    }
    }

    return OK;
}
}
