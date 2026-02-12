restore_current_state(save_state_T *sst)
{

    restore_typeahead(&sst->tabuf, FALSE);

    msg_scroll = sst->save_msg_scroll;
    restart_edit = sst->save_restart_edit;
    p_im = sst->save_insertmode;
    finish_op = sst->save_finish_op;
    opcount = sst->save_opcount;
    reg_executing = sst->save_reg_executing;
    pending_end_reg_executing = sst->save_pending_end_reg_executing;
    msg_didout |= sst->save_msg_didout;
    current_sctx.sc_version = sst->save_script_version;


    State = sst->save_State;
#ifdef CURSOR_SHAPE
    ui_cursor_shape();
#endif
}
