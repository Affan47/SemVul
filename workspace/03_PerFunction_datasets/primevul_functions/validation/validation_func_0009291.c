ex_stop(exarg_T *eap)
{


    if (!check_restricted())
    {
	if (!eap->forceit)
	    autowrite_all();
	apply_autocmds(EVENT_VIMSUSPEND, NULL, NULL, FALSE, NULL);
	windgoto((int)Rows - 1, 0);
	out_char('\n');
	out_flush();
	stoptermcap();
	out_flush();
#ifdef FEAT_TITLE
	mch_restore_title(SAVE_RESTORE_BOTH);
#endif
	ui_suspend();
#ifdef FEAT_TITLE
	maketitle();
	resettitle();
#endif
	starttermcap();
	scroll_start();
	redraw_later_clear();
	shell_resized();
	apply_autocmds(EVENT_VIMRESUME, NULL, NULL, FALSE, NULL);
    }
}
