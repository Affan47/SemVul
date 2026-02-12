op_yank(oparg_T *oap, int deleting, int mess)
{
    long		y_idx;
    yankreg_T		*curr;
    yankreg_T		newreg;
    char_u		**new_ptr;
    linenr_T		lnum;
    long		j;
    int			yanktype = oap->motion_type;
    long		yanklines = oap->line_count;
    linenr_T		yankendlnum = oap->end.lnum;
    char_u		*p;
    char_u		*pnew;
    struct block_def	bd;
#if defined(FEAT_CLIPBOARD) && defined(FEAT_X11)
    int			did_star = FALSE;
#endif


    if (oap->regname != 0 && !valid_yank_reg(oap->regname, TRUE))
    {
	beep_flush();
	return FAIL;
    }
    if (oap->regname == '_')
	return OK;

#ifdef FEAT_CLIPBOARD
    if (!clip_star.available && oap->regname == '*')
	oap->regname = 0;
    else if (!clip_plus.available && oap->regname == '+')
	oap->regname = 0;
#endif

    if (!deleting)
	get_yank_register(oap->regname, TRUE);

    curr = y_current;

    if (y_append && y_current->y_array != NULL)
	y_current = &newreg;
    else
	free_yank_all();


    if (       oap->motion_type == MCHAR
	    && oap->start.col == 0
	    && !oap->inclusive
	    && (!oap->is_VIsual || *p_sel == 'o')
	    && !oap->block_mode
	    && oap->end.col == 0
	    && yanklines > 1)
    {
	yanktype = MLINE;
	--yankendlnum;
	--yanklines;
    }

    y_current->y_size = yanklines;
    y_current->y_type = yanktype;
    y_current->y_width = 0;
    y_current->y_array = lalloc_clear(sizeof(char_u *) * yanklines, TRUE);
    if (y_current->y_array == NULL)
    {
	y_current = curr;
	return FAIL;
    }
#ifdef FEAT_VIMINFO
    y_current->y_time_set = vim_time();
#endif

    y_idx = 0;
    lnum = oap->start.lnum;

    if (oap->block_mode)
    {

	y_current->y_type = MBLOCK;
	y_current->y_width = oap->end_vcol - oap->start_vcol;

	if (curwin->w_curswant == MAXCOL && y_current->y_width > 0)
	    y_current->y_width--;
    }

    for ( ; lnum <= yankendlnum; lnum++, y_idx++)
    {
	switch (y_current->y_type)
	{
	    case MBLOCK:
		block_prep(oap, &bd, lnum, FALSE);
		if (yank_copy_line(&bd, y_idx, oap->excl_tr_ws) == FAIL)
		    goto fail;
		break;

	    case MLINE:
		if ((y_current->y_array[y_idx] =
					    vim_strsave(ml_get(lnum))) == NULL)
		    goto fail;
		break;

	    case MCHAR:
		{
		    colnr_T startcol = 0, endcol = MAXCOL;
		    int	    is_oneChar = FALSE;
		    colnr_T cs, ce;

		    p = ml_get(lnum);
		    bd.startspaces = 0;
		    bd.endspaces = 0;

		    if (lnum == oap->start.lnum)
		    {
			startcol = oap->start.col;
			if (virtual_op)
			{
			    getvcol(curwin, &oap->start, &cs, NULL, &ce);
			    if (ce != cs && oap->start.coladd > 0)
			    {


				bd.startspaces = (ce - cs + 1)
							  - oap->start.coladd;
				startcol++;
			    }
			}
		    }

		    if (lnum == oap->end.lnum)
		    {
			endcol = oap->end.col;
			if (virtual_op)
			{
			    getvcol(curwin, &oap->end, &cs, NULL, &ce);
			    if (p[endcol] == NUL || (cs + oap->end.coladd < ce


					&& (*mb_head_off)(p, p + endcol) == 0))
			    {
				if (oap->start.lnum == oap->end.lnum
					    && oap->start.col == oap->end.col)
				{

				    is_oneChar = TRUE;
				    bd.startspaces = oap->end.coladd
					 - oap->start.coladd + oap->inclusive;
				    endcol = startcol;
				}
				else
				{
				    bd.endspaces = oap->end.coladd
							     + oap->inclusive;
				    endcol -= oap->inclusive;
				}
			    }
			}
		    }
		    if (endcol == MAXCOL)
			endcol = (colnr_T)STRLEN(p);
		    if (startcol > endcol || is_oneChar)
			bd.textlen = 0;
		    else
			bd.textlen = endcol - startcol + oap->inclusive;
		    bd.textstart = p + startcol;
		    if (yank_copy_line(&bd, y_idx, FALSE) == FAIL)
			goto fail;
		    break;
		}

	}
    }

    if (curr != y_current)
    {
	new_ptr = ALLOC_MULT(char_u *, curr->y_size + y_current->y_size);
	if (new_ptr == NULL)
	    goto fail;
	for (j = 0; j < curr->y_size; ++j)
	    new_ptr[j] = curr->y_array[j];
	vim_free(curr->y_array);
	curr->y_array = new_ptr;
#ifdef FEAT_VIMINFO
	curr->y_time_set = vim_time();
#endif

	if (yanktype == MLINE)
	    curr->y_type = MLINE;


	if (curr->y_type == MCHAR && vim_strchr(p_cpo, CPO_REGAPPEND) == NULL)
	{
	    pnew = alloc(STRLEN(curr->y_array[curr->y_size - 1])
					  + STRLEN(y_current->y_array[0]) + 1);
	    if (pnew == NULL)
	    {
		y_idx = y_current->y_size - 1;
		goto fail;
	    }
	    STRCPY(pnew, curr->y_array[--j]);
	    STRCAT(pnew, y_current->y_array[0]);
	    vim_free(curr->y_array[j]);
	    vim_free(y_current->y_array[0]);
	    curr->y_array[j++] = pnew;
	    y_idx = 1;
	}
	else
	    y_idx = 0;
	while (y_idx < y_current->y_size)
	    curr->y_array[j++] = y_current->y_array[y_idx++];
	curr->y_size = j;
	vim_free(y_current->y_array);
	y_current = curr;
    }

    if (mess)
    {
	if (yanktype == MCHAR
		&& !oap->block_mode
		&& yanklines == 1)
	    yanklines = 0;

	if (yanklines > p_report)
	{
	    char namebuf[100];

	    if (oap->regname == NUL)
		*namebuf = NUL;
	    else
		vim_snprintf(namebuf, sizeof(namebuf),
						_(" into \"%c"), oap->regname);


	    update_topline_redraw();
	    if (oap->block_mode)
	    {
		smsg(NGETTEXT("block of %ld line yanked%s",
				     "block of %ld lines yanked%s", yanklines),
			yanklines, namebuf);
	    }
	    else
	    {
		smsg(NGETTEXT("%ld line yanked%s",
					      "%ld lines yanked%s", yanklines),
			yanklines, namebuf);
	    }
	}
    }

    if ((cmdmod.cmod_flags & CMOD_LOCKMARKS) == 0)
    {

	curbuf->b_op_start = oap->start;
	curbuf->b_op_end = oap->end;
	if (yanktype == MLINE && !oap->block_mode)
	{
	    curbuf->b_op_start.col = 0;
	    curbuf->b_op_end.col = MAXCOL;
	}
    }

#ifdef FEAT_CLIPBOARD


    if (clip_star.available
	    && (curr == &(y_regs[STAR_REGISTER])
		|| (!deleting && oap->regname == 0
		   && ((clip_unnamed | clip_unnamed_saved) & CLIP_UNNAMED))))
    {
	if (curr != &(y_regs[STAR_REGISTER]))

	    copy_yank_reg(&(y_regs[STAR_REGISTER]));

	clip_own_selection(&clip_star);
	clip_gen_set_selection(&clip_star);
# ifdef FEAT_X11
	did_star = TRUE;
# endif
    }

# ifdef FEAT_X11


    if (clip_plus.available
	    && (curr == &(y_regs[PLUS_REGISTER])
		|| (!deleting && oap->regname == 0
		  && ((clip_unnamed | clip_unnamed_saved) &
							  CLIP_UNNAMED_PLUS))))
    {
	if (curr != &(y_regs[PLUS_REGISTER]))

	    copy_yank_reg(&(y_regs[PLUS_REGISTER]));

	clip_own_selection(&clip_plus);
	clip_gen_set_selection(&clip_plus);
	if (!clip_isautosel_star()
		&& !clip_isautosel_plus()
		&& !((clip_unnamed | clip_unnamed_saved) == CLIP_UNNAMED_PLUS)
		&& !did_star
		&& curr == &(y_regs[PLUS_REGISTER]))
	{
	    copy_yank_reg(&(y_regs[STAR_REGISTER]));
	    clip_own_selection(&clip_star);
	    clip_gen_set_selection(&clip_star);
	}
    }
# endif
#endif

#if defined(FEAT_EVAL)
    if (!deleting && has_textyankpost())
	yank_do_autocmd(oap, y_current);
#endif

    return OK;

fail:
    free_yank(y_idx + 1);
    y_current = curr;
    return FAIL;
}
