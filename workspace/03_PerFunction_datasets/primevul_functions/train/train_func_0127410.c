nv_put_opt(cmdarg_T *cap, int fix_indent)
{
    int		regname = 0;
    void	*reg1 = NULL, *reg2 = NULL;
    int		empty = FALSE;
    int		was_visual = FALSE;
    int		dir;
    int		flags = 0;

    if (cap->oap->op_type != OP_NOP)
    {
#ifdef FEAT_DIFF

	if (cap->oap->op_type == OP_DELETE && cap->cmdchar == 'p')
	{
	    clearop(cap->oap);
	    nv_diffgetput(TRUE, cap->opcount);
	}
	else
#endif
	clearopbeep(cap->oap);
    }
#ifdef FEAT_JOB_CHANNEL
    else if (bt_prompt(curbuf) && !prompt_curpos_editable())
    {
	clearopbeep(cap->oap);
    }
#endif
    else
    {
	if (fix_indent)
	{
	    dir = (cap->cmdchar == ']' && cap->nchar == 'p')
							 ? FORWARD : BACKWARD;
	    flags |= PUT_FIXINDENT;
	}
	else
	    dir = (cap->cmdchar == 'P'
		    || ((cap->cmdchar == 'g' || cap->cmdchar == 'z')
			&& cap->nchar == 'P')) ? BACKWARD : FORWARD;
	prep_redo_cmd(cap);
	if (cap->cmdchar == 'g')
	    flags |= PUT_CURSEND;
	else if (cap->cmdchar == 'z')
	    flags |= PUT_BLOCK_INNER;

	if (VIsual_active)
	{


	    was_visual = TRUE;
	    regname = cap->oap->regname;
#ifdef FEAT_CLIPBOARD
	    adjust_clip_reg(&regname);
#endif
	   if (regname == 0 || regname == '"'
				     || VIM_ISDIGIT(regname) || regname == '-'
#ifdef FEAT_CLIPBOARD
		    || (clip_unnamed && (regname == '*' || regname == '+'))
#endif

		    )
	    {


		reg1 = get_register(regname, TRUE);
	    }


	    cap->cmdchar = 'd';
	    cap->nchar = NUL;
	    cap->oap->regname = NUL;
	    ++msg_silent;
	    nv_operator(cap);
	    do_pending_operator(cap, 0, FALSE);
	    empty = (curbuf->b_ml.ml_flags & ML_EMPTY);
	    --msg_silent;


	    cap->oap->regname = regname;

	    if (reg1 != NULL)
	    {


		reg2 = get_register(regname, FALSE);
		put_register(regname, reg1);
	    }


	    if (VIsual_mode == 'V')
		flags |= PUT_LINE;
	    else if (VIsual_mode == 'v')
		flags |= PUT_LINE_SPLIT;
	    if (VIsual_mode == Ctrl_V && dir == FORWARD)
		flags |= PUT_LINE_FORWARD;
	    dir = BACKWARD;
	    if ((VIsual_mode != 'V'
			&& curwin->w_cursor.col < curbuf->b_op_start.col)
		    || (VIsual_mode == 'V'
			&& curwin->w_cursor.lnum < curbuf->b_op_start.lnum))


		dir = FORWARD;

	    VIsual_active = TRUE;
	}
	do_put(cap->oap->regname, NULL, dir, cap->count1, flags);


	if (reg2 != NULL)
	    put_register(regname, reg2);


	if (was_visual)
	{
	    curbuf->b_visual.vi_start = curbuf->b_op_start;
	    curbuf->b_visual.vi_end = curbuf->b_op_end;

	    if (*p_sel == 'e')
		inc(&curbuf->b_visual.vi_end);
	}


	if (empty && *ml_get(curbuf->b_ml.ml_line_count) == NUL)
	{
	    ml_delete_flags(curbuf->b_ml.ml_line_count, ML_DEL_MESSAGE);
	    deleted_lines(curbuf->b_ml.ml_line_count + 1, 1);


	    if (curwin->w_cursor.lnum > curbuf->b_ml.ml_line_count)
	    {
		curwin->w_cursor.lnum = curbuf->b_ml.ml_line_count;
		coladvance((colnr_T)MAXCOL);
	    }
	}
	auto_format(FALSE, TRUE);
    }
}
