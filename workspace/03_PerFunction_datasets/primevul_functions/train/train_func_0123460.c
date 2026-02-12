win_free_all(void)
{
    int		dummy;

    while (first_tabpage->tp_next != NULL)
	tabpage_close(TRUE);

    if (aucmd_win != NULL)
    {
	(void)win_free_mem(aucmd_win, &dummy, NULL);
	aucmd_win = NULL;
    }
# ifdef FEAT_TEXT_PROP
    close_all_popups();
# endif

    while (firstwin != NULL)
	(void)win_free_mem(firstwin, &dummy, NULL);


    curwin = NULL;
}
