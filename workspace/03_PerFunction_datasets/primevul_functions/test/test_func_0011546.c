nv_screengo(oparg_T *oap, int dir, long dist)
{
    int		linelen = linetabsize(ml_get_curline());
    int		retval = OK;
    int		atend = FALSE;
    int		n;
    int		col_off1;
    int		col_off2;
    int		width1;
    int		width2;

    oap->motion_type = MCHAR;
    oap->inclusive = (curwin->w_curswant == MAXCOL);

    col_off1 = curwin_col_off();
    col_off2 = col_off1 - curwin_col_off2();
    width1 = curwin->w_width - col_off1;
    width2 = curwin->w_width - col_off2;
    if (width2 == 0)
	width2 = 1;

    if (curwin->w_width != 0)
    {


      if (curwin->w_curswant == MAXCOL)
      {
	atend = TRUE;
	validate_virtcol();
	if (width1 <= 0)
	    curwin->w_curswant = 0;
	else
	{
	    curwin->w_curswant = width1 - 1;
	    if (curwin->w_virtcol > curwin->w_curswant)
		curwin->w_curswant += ((curwin->w_virtcol
			     - curwin->w_curswant - 1) / width2 + 1) * width2;
	}
      }
      else
      {
	if (linelen > width1)
	    n = ((linelen - width1 - 1) / width2 + 1) * width2 + width1;
	else
	    n = width1;
	if (curwin->w_curswant >= (colnr_T)n)
	    curwin->w_curswant = n - 1;
      }

      while (dist--)
      {
	if (dir == BACKWARD)
	{
	    if ((long)curwin->w_curswant >= width1
#ifdef FEAT_FOLDING
		    && !hasFolding(curwin->w_cursor.lnum, NULL, NULL)
#endif
	       )


		curwin->w_curswant -= width2;
	    else
	    {

#ifdef FEAT_FOLDING


		if (!(fdo_flags & FDO_ALL))
		    (void)hasFolding(curwin->w_cursor.lnum,
						&curwin->w_cursor.lnum, NULL);
#endif
		if (curwin->w_cursor.lnum == 1)
		{
		    retval = FAIL;
		    break;
		}
		--curwin->w_cursor.lnum;

		linelen = linetabsize(ml_get_curline());
		if (linelen > width1)
		    curwin->w_curswant += (((linelen - width1 - 1) / width2)
								+ 1) * width2;
	    }
	}
	else
	{
	    if (linelen > width1)
		n = ((linelen - width1 - 1) / width2 + 1) * width2 + width1;
	    else
		n = width1;
	    if (curwin->w_curswant + width2 < (colnr_T)n
#ifdef FEAT_FOLDING
		    && !hasFolding(curwin->w_cursor.lnum, NULL, NULL)
#endif
		    )

		curwin->w_curswant += width2;
	    else
	    {

#ifdef FEAT_FOLDING

		(void)hasFolding(curwin->w_cursor.lnum, NULL,
						      &curwin->w_cursor.lnum);
#endif
		if (curwin->w_cursor.lnum == curbuf->b_ml.ml_line_count)
		{
		    retval = FAIL;
		    break;
		}
		curwin->w_cursor.lnum++;
		curwin->w_curswant %= width2;


		if (curwin->w_curswant >= width1)
		    curwin->w_curswant -= width2;
		linelen = linetabsize(ml_get_curline());
	    }
	}
      }
    }

    if (virtual_active() && atend)
	coladvance(MAXCOL);
    else
	coladvance(curwin->w_curswant);

    if (curwin->w_cursor.col > 0 && curwin->w_p_wrap)
    {
	colnr_T virtcol;
	int	c;


	validate_virtcol();
	virtcol = curwin->w_virtcol;
#if defined(FEAT_LINEBREAK)
	if (virtcol > (colnr_T)width1 && *get_showbreak_value(curwin) != NUL)
	    virtcol -= vim_strsize(get_showbreak_value(curwin));
#endif

	c = (*mb_ptr2char)(ml_get_cursor());
	if (dir == FORWARD && virtcol < curwin->w_curswant
		&& (curwin->w_curswant <= (colnr_T)width1)
		&& !vim_isprintc(c) && c > 255)
	    oneright();

	if (virtcol > curwin->w_curswant
		&& (curwin->w_curswant < (colnr_T)width1
		    ? (curwin->w_curswant > (colnr_T)width1 / 2)
		    : ((curwin->w_curswant - width1) % width2
						      > (colnr_T)width2 / 2)))
	    --curwin->w_cursor.col;
    }

    if (atend)
	curwin->w_curswant = MAXCOL;

    return retval;
}
