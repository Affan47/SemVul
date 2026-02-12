nv_edit(cmdarg_T *cap)
{

    if (cap->cmdchar == K_INS || cap->cmdchar == K_KINS)
	cap->cmdchar = 'i';


    if (VIsual_active && (cap->cmdchar == 'A' || cap->cmdchar == 'I'))
    {
#ifdef FEAT_TERMINAL
	if (term_in_normal_mode())
	{
	    end_visual_mode();
	    clearop(cap->oap);
	    term_enter_job_mode();
	    return;
	}
#endif
	v_visop(cap);
    }


    else if ((cap->cmdchar == 'a' || cap->cmdchar == 'i')
	    && (cap->oap->op_type != OP_NOP || VIsual_active))
    {
#ifdef FEAT_TEXTOBJ
	nv_object(cap);
#else
	clearopbeep(cap->oap);
#endif
    }
#ifdef FEAT_TERMINAL
    else if (term_in_normal_mode())
    {
	clearop(cap->oap);
	term_enter_job_mode();
	return;
    }
#endif
    else if (!curbuf->b_p_ma && !p_im)
    {

	emsg(_(e_cannot_make_changes_modifiable_is_off));
	clearop(cap->oap);
	if (cap->cmdchar == K_PS)

	    bracketed_paste(PASTE_INSERT, TRUE, NULL);
    }
    else if (cap->cmdchar == K_PS && VIsual_active)
    {
	pos_T old_pos = curwin->w_cursor;
	pos_T old_visual = VIsual;


	if (VIsual_mode == 'V' || curwin->w_cursor.lnum != VIsual.lnum)
	{
	    shift_delete_registers();
	    cap->oap->regname = '1';
	}
	else
	    cap->oap->regname = '-';
	cap->cmdchar = 'd';
	cap->nchar = NUL;
	nv_operator(cap);
	do_pending_operator(cap, 0, FALSE);
	cap->cmdchar = K_PS;


	if (*ml_get_cursor() != NUL && LT_POS(curwin->w_cursor, old_pos)
				       && LT_POS(curwin->w_cursor, old_visual))
	    inc_cursor();


	invoke_edit(cap, FALSE, cap->cmdchar, FALSE);
    }
    else if (!checkclearopq(cap->oap))
    {
	switch (cap->cmdchar)
	{
	    case 'A':
		set_cursor_for_append_to_line();
		break;

	    case 'I':
		if (vim_strchr(p_cpo, CPO_INSEND) == NULL)
		    beginline(BL_WHITE);
		else
		    beginline(BL_WHITE|BL_FIX);
		break;

	    case K_PS:


		if (curwin->w_cursor.col == 0)
		    break;


	    case 'a':


		if (virtual_active()
			&& (curwin->w_cursor.coladd > 0
			    || *ml_get_cursor() == NUL
			    || *ml_get_cursor() == TAB))
		    curwin->w_cursor.coladd++;
		else if (*ml_get_cursor() != NUL)
		    inc_cursor();
		break;
	}

	if (curwin->w_cursor.coladd && cap->cmdchar != 'A')
	{
	    int save_State = State;


	    State = INSERT;
	    coladvance(getviscol());
	    State = save_State;
	}

	invoke_edit(cap, FALSE, cap->cmdchar, FALSE);
    }
    else if (cap->cmdchar == K_PS)

	bracketed_paste(PASTE_INSERT, TRUE, NULL);
}
