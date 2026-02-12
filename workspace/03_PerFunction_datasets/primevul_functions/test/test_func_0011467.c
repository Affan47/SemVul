nv_colon(cmdarg_T *cap)
{
    int	old_p_im;
    int	cmd_result;
    int	is_cmdkey = cap->cmdchar == K_COMMAND
					   || cap->cmdchar == K_SCRIPT_COMMAND;
    int	flags;

    if (VIsual_active && !is_cmdkey)
	nv_operator(cap);
    else
    {
	if (cap->oap->op_type != OP_NOP)
	{

	    cap->oap->motion_type = MCHAR;
	    cap->oap->inclusive = FALSE;
	}
	else if (cap->count0 && !is_cmdkey)
	{

	    stuffcharReadbuff('.');
	    if (cap->count0 > 1)
	    {
		stuffReadbuff((char_u *)",.+");
		stuffnumReadbuff((long)cap->count0 - 1L);
	    }
	}


	if (KeyTyped)
	    compute_cmdrow();

	old_p_im = p_im;


	flags = cap->oap->op_type != OP_NOP ? DOCMD_KEEPLINE : 0;
	if (is_cmdkey)
	    cmd_result = do_cmdkey_command(cap->cmdchar, flags);
	else
	    cmd_result = do_cmdline(NULL, getexline, NULL, flags);


	if (p_im != old_p_im)
	{
	    if (p_im)
		restart_edit = 'i';
	    else
		restart_edit = 0;
	}

	if (cmd_result == FAIL)

	    clearop(cap->oap);
	else if (cap->oap->op_type != OP_NOP
		&& (cap->oap->start.lnum > curbuf->b_ml.ml_line_count
		    || cap->oap->start.col >
			       (colnr_T)STRLEN(ml_get(cap->oap->start.lnum))
		    || did_emsg
		    ))

	    clearopbeep(cap->oap);
    }
}
