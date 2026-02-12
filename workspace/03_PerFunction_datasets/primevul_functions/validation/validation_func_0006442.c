ins_compl_continue_search(char_u *line)
{

    compl_cont_status &= ~CONT_INTRPT;
    if (ctrl_x_mode_normal() || ctrl_x_mode_path_patterns()
						|| ctrl_x_mode_path_defines())
    {
	if (compl_startpos.lnum != curwin->w_cursor.lnum)
	{


	    compl_col = (colnr_T)getwhitecols(line);
	    compl_startpos.col = compl_col;
	    compl_startpos.lnum = curwin->w_cursor.lnum;
	    compl_cont_status &= ~CONT_SOL;
	}
	else
	{


	    if (compl_cont_status & CONT_S_IPOS)
	    {
		compl_cont_status |= CONT_SOL;
		compl_startpos.col = (colnr_T)(skipwhite(
			    line + compl_length
			    + compl_startpos.col) - line);
	    }
	    compl_col = compl_startpos.col;
	}
	compl_length = curwin->w_cursor.col - (int)compl_col;


#define	MIN_SPACE 75
	if (compl_length > (IOSIZE - MIN_SPACE))
	{
	    compl_cont_status &= ~CONT_SOL;
	    compl_length = (IOSIZE - MIN_SPACE);
	    compl_col = curwin->w_cursor.col - compl_length;
	}
	compl_cont_status |= CONT_ADDING | CONT_N_ADDS;
	if (compl_length < 1)
	    compl_cont_status &= CONT_LOCAL;
    }
    else if (ctrl_x_mode_line_or_eval())
	compl_cont_status = CONT_ADDING | CONT_N_ADDS;
    else
	compl_cont_status = 0;
}
