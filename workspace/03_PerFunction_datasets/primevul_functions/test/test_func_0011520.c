normal_cmd_need_to_wait_for_msg(cmdarg_T *cap, pos_T *old_pos)
{


    return (       ((p_smd
		    && msg_silent == 0
		    && (restart_edit != 0
			|| (VIsual_active
			    && old_pos->lnum == curwin->w_cursor.lnum
			    && old_pos->col == curwin->w_cursor.col)
		       )
		    && (clear_cmdline
			|| redraw_cmdline)
		    && (msg_didout || (msg_didany && msg_scroll))
		    && !msg_nowait
		    && KeyTyped)
		|| (restart_edit != 0
		    && !VIsual_active
		    && (msg_scroll
			|| emsg_on_display)))
	    && cap->oap->regname == 0
	    && !(cap->retval & CA_COMMAND_BUSY)
	    && stuff_empty()
	    && typebuf_typed()
	    && emsg_silent == 0
	    && !in_assert_fails
	    && !did_wait_return
	    && cap->oap->op_type == OP_NOP);
}
