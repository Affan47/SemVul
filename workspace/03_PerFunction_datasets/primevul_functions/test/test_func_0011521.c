nv_object(
    cmdarg_T	*cap)
{
    int		flag;
    int		include;
    char_u	*mps_save;

    if (cap->cmdchar == 'i')
	include = FALSE;
    else
	include = TRUE;


    mps_save = curbuf->b_p_mps;
    curbuf->b_p_mps = (char_u *)"(:),{:},[:],<:>";

    switch (cap->nchar)
    {
	case 'w':
		flag = current_word(cap->oap, cap->count1, include, FALSE);
		break;
	case 'W':
		flag = current_word(cap->oap, cap->count1, include, TRUE);
		break;
	case 'b':
	case '(':
	case ')':
		flag = current_block(cap->oap, cap->count1, include, '(', ')');
		break;
	case 'B':
	case '{':
	case '}':
		flag = current_block(cap->oap, cap->count1, include, '{', '}');
		break;
	case '[':
	case ']':
		flag = current_block(cap->oap, cap->count1, include, '[', ']');
		break;
	case '<':
	case '>':
		flag = current_block(cap->oap, cap->count1, include, '<', '>');
		break;
	case 't':


		cap->retval |= CA_NO_ADJ_OP_END;
		flag = current_tagblock(cap->oap, cap->count1, include);
		break;
	case 'p':
		flag = current_par(cap->oap, cap->count1, include, 'p');
		break;
	case 's':
		flag = current_sent(cap->oap, cap->count1, include);
		break;
	case '"':
	case '\'':
	case '`':
		flag = current_quote(cap->oap, cap->count1, include,
								  cap->nchar);
		break;
#if 0
	case 'S':
	case 'f':
	case 'u':
#endif
	default:
		flag = FAIL;
		break;
    }

    curbuf->b_p_mps = mps_save;
    if (flag == FAIL)
	clearopbeep(cap->oap);
    adjust_cursor_col();
    curwin->w_set_curswant = TRUE;
}
