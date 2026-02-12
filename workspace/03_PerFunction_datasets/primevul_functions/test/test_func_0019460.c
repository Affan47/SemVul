ex_pedit(exarg_T *eap)
{
    win_T	*curwin_save = curwin;

    if (ERROR_IF_ANY_POPUP_WINDOW)
	return;


    g_do_tagpreview = p_pvh;
    prepare_tagpreview(TRUE, TRUE, FALSE);


    do_exedit(eap, NULL);

    if (curwin != curwin_save && win_valid(curwin_save))
    {

	validate_cursor();
	redraw_later(UPD_VALID);
	win_enter(curwin_save, TRUE);
    }
# ifdef FEAT_PROP_POPUP
    else if (WIN_IS_POPUP(curwin))
    {

	win_enter(firstwin, TRUE);
    }
# endif
    g_do_tagpreview = 0;
}
