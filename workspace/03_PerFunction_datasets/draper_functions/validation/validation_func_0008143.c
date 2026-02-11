evt_cmdseq_selection_changed(GtkTreeSelection *sel, gpointer user)
{
	P_CmdSeq	*page = user;
	GtkTreeIter	iter;
	CmdSeq		*cmdseq;

	if((cmdseq = cmdseq_get_selected(page, &iter)) != NULL)
		set_widgets(page);
	else
		reset_widgets(page);
}
