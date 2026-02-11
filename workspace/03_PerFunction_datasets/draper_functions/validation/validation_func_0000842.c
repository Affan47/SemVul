set_ptrdlglab(GtkWidget *dlg, const struct spptr *pp)
{
	char  *pr = gprompt(1694);
	GString *labp = g_string_new(NULL);
	GtkWidget  *lab;

	if  (pp->spp_netid)
		g_string_printf(labp, "%s %s:%s", pr, look_host(pp->spp_netid), pp->spp_ptr);
	else
		g_string_printf(labp, "%s %s", pr, pp->spp_ptr);
	free(pr);
	lab = gtk_label_new(labp->str);
	g_string_free(labp, TRUE);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dlg)->vbox), lab, FALSE, FALSE, DEF_DLG_VPAD);
}
