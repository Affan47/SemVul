u_saveline(lnum)
	linenr_t lnum;
{
	if (lnum == curbuf->b_u_line_lnum)
		return;
	if (lnum < 1 || lnum > curbuf->b_ml.ml_line_count)
		return;
	u_clearline();
	curbuf->b_u_line_lnum = lnum;
	if (curwin->w_cursor.lnum == lnum)
		curbuf->b_u_line_colnr = curwin->w_cursor.col;
	else
		curbuf->b_u_line_colnr = 0;
	curbuf->b_u_line_ptr = u_save_line(lnum);
}
