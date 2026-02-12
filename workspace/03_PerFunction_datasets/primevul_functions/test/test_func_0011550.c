nv_down(cmdarg_T *cap)
{
    if (mod_mask & MOD_MASK_SHIFT)
    {

	cap->arg = FORWARD;
	nv_page(cap);
    }
#if defined(FEAT_QUICKFIX)

    else if (bt_quickfix(curbuf) && cap->cmdchar == CAR)
	qf_view_result(FALSE);
#endif
    else
    {
#ifdef FEAT_CMDWIN

	if (cmdwin_type != 0 && cap->cmdchar == CAR)
	    cmdwin_result = CAR;
	else
#endif
#ifdef FEAT_JOB_CHANNEL

	if (bt_prompt(curbuf) && cap->cmdchar == CAR
		       && curwin->w_cursor.lnum == curbuf->b_ml.ml_line_count)
	{
	    invoke_prompt_callback();
	    if (restart_edit == 0)
		restart_edit = 'a';
	}
	else
#endif
	{
	    cap->oap->motion_type = MLINE;
	    if (cursor_down(cap->count1, cap->oap->op_type == OP_NOP) == FAIL)
		clearopbeep(cap->oap);
	    else if (cap->arg)
		beginline(BL_WHITE | BL_FIX);
	}
    }
}
