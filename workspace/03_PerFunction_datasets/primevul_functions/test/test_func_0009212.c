do_filter(
    linenr_T	line1,
    linenr_T	line2,
    exarg_T	*eap,
    char_u	*cmd,
    int		do_in,
    int		do_out)
{
    char_u	*itmp = NULL;
    char_u	*otmp = NULL;
    linenr_T	linecount;
    linenr_T	read_linecount;
    pos_T	cursor_save;
    char_u	*cmd_buf;
    buf_T	*old_curbuf = curbuf;
    int		shell_flags = 0;
    pos_T	orig_start = curbuf->b_op_start;
    pos_T	orig_end = curbuf->b_op_end;
    int		save_cmod_flags = cmdmod.cmod_flags;
#ifdef FEAT_FILTERPIPE
    int		stmp = p_stmp;
#endif

    if (*cmd == NUL)
	return;


    cmdmod.cmod_flags &= ~CMOD_LOCKMARKS;

    cursor_save = curwin->w_cursor;
    linecount = line2 - line1 + 1;
    curwin->w_cursor.lnum = line1;
    curwin->w_cursor.col = 0;
    changed_line_abv_curs();
    invalidate_botline();


    if (do_out)
	shell_flags |= SHELL_DOOUT;

#ifdef FEAT_FILTERPIPE
# ifdef VIMDLL
    if (!gui.in_use && !gui.starting)
	stmp = 1;
# endif

    if (!do_in && do_out && !stmp)
    {

	shell_flags |= SHELL_READ;
	curwin->w_cursor.lnum = line2;
    }
    else if (do_in && !do_out && !stmp)
    {

	shell_flags |= SHELL_WRITE;
	curbuf->b_op_start.lnum = line1;
	curbuf->b_op_end.lnum = line2;
    }
    else if (do_in && do_out && !stmp)
    {


	shell_flags |= SHELL_READ|SHELL_WRITE;
	curbuf->b_op_start.lnum = line1;
	curbuf->b_op_end.lnum = line2;
	curwin->w_cursor.lnum = line2;
    }
    else
#endif
	if ((do_in && (itmp = vim_tempname('i', FALSE)) == NULL)
		|| (do_out && (otmp = vim_tempname('o', FALSE)) == NULL))
	{
	    emsg(_(e_cant_get_temp_file_name));
	    goto filterend;
	}


    ++no_wait_return;
    if (itmp != NULL && buf_write(curbuf, itmp, NULL, line1, line2, eap,
					   FALSE, FALSE, FALSE, TRUE) == FAIL)
    {
	msg_putchar('\n');
	--no_wait_return;
#if defined(FEAT_EVAL)
	if (!aborting())
#endif
	    (void)semsg(_(e_cant_create_file_str), itmp);
	goto filterend;
    }
    if (curbuf != old_curbuf)
	goto filterend;

    if (!do_out)
	msg_putchar('\n');


    cmd_buf = make_filter_cmd(cmd, itmp, otmp);
    if (cmd_buf == NULL)
	goto filterend;

    windgoto((int)Rows - 1, 0);
    cursor_on();


    if (!do_out || STRCMP(p_srr, ">") == 0 || !do_in)
	redraw_later_clear();

    if (do_out)
    {
	if (u_save((linenr_T)(line2), (linenr_T)(line2 + 1)) == FAIL)
	{
	    vim_free(cmd_buf);
	    goto error;
	}
	redraw_curbuf_later(VALID);
    }
    read_linecount = curbuf->b_ml.ml_line_count;


    if (call_shell(cmd_buf, SHELL_FILTER | SHELL_COOKED | shell_flags))
    {
	redraw_later_clear();
	wait_return(FALSE);
    }
    vim_free(cmd_buf);

    did_check_timestamps = FALSE;
    need_check_timestamps = TRUE;


    ui_breakcheck();
    got_int = FALSE;

    if (do_out)
    {
	if (otmp != NULL)
	{
	    if (readfile(otmp, NULL, line2, (linenr_T)0, (linenr_T)MAXLNUM,
						    eap, READ_FILTER) != OK)
	    {
#if defined(FEAT_EVAL)
		if (!aborting())
#endif
		{
		    msg_putchar('\n');
		    semsg(_(e_cant_read_file_str), otmp);
		}
		goto error;
	    }
	    if (curbuf != old_curbuf)
		goto filterend;
	}

	read_linecount = curbuf->b_ml.ml_line_count - read_linecount;

	if (shell_flags & SHELL_READ)
	{
	    curbuf->b_op_start.lnum = line2 + 1;
	    curbuf->b_op_end.lnum = curwin->w_cursor.lnum;
	    appended_lines_mark(line2, read_linecount);
	}

	if (do_in)
	{
	    if ((cmdmod.cmod_flags & CMOD_KEEPMARKS)
				     || vim_strchr(p_cpo, CPO_REMMARK) == NULL)
	    {
		if (read_linecount >= linecount)

		    mark_adjust(line1, line2, linecount, 0L);
		else if (save_cmod_flags & CMOD_LOCKMARKS)
		{


		    mark_adjust(line2 + 1, (linenr_T)MAXLNUM,
					       linecount - read_linecount, 0L);
		    mark_adjust(line1, line2, linecount, 0L);
		}
		else
		{


		    mark_adjust(line1, line1 + read_linecount - 1,
								linecount, 0L);
		    mark_adjust(line1 + read_linecount, line2, MAXLNUM, 0L);
		}
	    }


	    curwin->w_cursor.lnum = line1;
	    del_lines(linecount, TRUE);
	    curbuf->b_op_start.lnum -= linecount;
	    curbuf->b_op_end.lnum -= linecount;
	    write_lnum_adjust(-linecount);

#ifdef FEAT_FOLDING
	    foldUpdate(curwin, curbuf->b_op_start.lnum, curbuf->b_op_end.lnum);
#endif
	}
	else
	{


	    linecount = curbuf->b_op_end.lnum - curbuf->b_op_start.lnum + 1;
	    curwin->w_cursor.lnum = curbuf->b_op_end.lnum;
	}

	beginline(BL_WHITE | BL_FIX);
	--no_wait_return;

	if (linecount > p_report)
	{
	    if (do_in)
	    {
		vim_snprintf(msg_buf, sizeof(msg_buf),
				    _("%ld lines filtered"), (long)linecount);
		if (msg(msg_buf) && !msg_scroll)

		    set_keep_msg((char_u *)msg_buf, 0);
	    }
	    else
		msgmore((long)linecount);
	}
    }
    else
    {
error:

	curwin->w_cursor = cursor_save;
	--no_wait_return;
	wait_return(FALSE);
    }

filterend:

    cmdmod.cmod_flags = save_cmod_flags;
    if (curbuf != old_curbuf)
    {
	--no_wait_return;
	emsg(_(e_filter_autocommands_must_not_change_current_buffer));
    }
    else if (cmdmod.cmod_flags & CMOD_LOCKMARKS)
    {
	curbuf->b_op_start = orig_start;
	curbuf->b_op_end = orig_end;
    }

    if (itmp != NULL)
	mch_remove(itmp);
    if (otmp != NULL)
	mch_remove(otmp);
    vim_free(itmp);
    vim_free(otmp);
}
