ins_compl_new_leader(void)
{
    ins_compl_del_pum();
    ins_compl_delete();
    ins_bytes(compl_leader + get_compl_len());
    compl_used_match = FALSE;

    if (compl_started)
	ins_compl_set_original_text(compl_leader);
    else
    {
#ifdef FEAT_SPELL
	spell_bad_len = 0;
#endif


	pum_call_update_screen();
#ifdef FEAT_GUI
	if (gui.in_use)
	{

	    setcursor();
	    out_flush_cursor(FALSE, FALSE);
	}
#endif
	compl_restarting = TRUE;
	if (ins_complete(Ctrl_N, TRUE) == FAIL)
	    compl_cont_status = 0;
	compl_restarting = FALSE;
    }

    compl_enter_selects = !compl_used_match;


    ins_compl_show_pum();


    if (compl_match_array == NULL)
	compl_enter_selects = FALSE;
}
