ex_startinsert(exarg_T *eap)
{
    if (eap->forceit)
    {

	if (!curwin->w_cursor.lnum)
	    curwin->w_cursor.lnum = 1;
	set_cursor_for_append_to_line();
    }
#ifdef FEAT_TERMINAL

    if (term_job_running(curbuf->b_term))
	return;
#endif


    if (State & MODE_INSERT)
	return;

    if (eap->cmdidx == CMD_startinsert)
	restart_edit = 'a';
    else if (eap->cmdidx == CMD_startreplace)
	restart_edit = 'R';
    else
	restart_edit = 'V';

    if (!eap->forceit)
    {
	if (eap->cmdidx == CMD_startinsert)
	    restart_edit = 'i';
	curwin->w_curswant = 0;
    }

    if (VIsual_active)
	showmode();
}
