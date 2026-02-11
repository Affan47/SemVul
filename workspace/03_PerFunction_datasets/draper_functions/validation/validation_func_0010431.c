e2_confdlg_choose_plugin_cb (GtkWidget *button, E2_OptionSet *set)
{
	GtkTreeView *tvw = GTK_TREE_VIEW (set->widget);
	GtkTreePath *tpath;
	gtk_tree_view_get_cursor (tvw, &tpath, NULL);
	if (tpath == NULL)
		return;

	E2_TreeCfgData *data = MALLOCATE (E2_TreeCfgData);
	CHECKALLOCATEDWARN (data, return;);
	data->set = set;
	data->tpath = tpath;

	GtkTreeIter iter;
	gchar *pname, *ppath;
	gtk_tree_model_get_iter (set->ex.tree.model, &iter, tpath);
	gtk_tree_model_get (set->ex.tree.model, &iter, 5, &pname, 6, &ppath, -1);
	if (*pname == '\0')
	{
		g_free (ppath);
		ppath = NULL;
	}
	else
	{
		if (*ppath == '\0')
		{
			g_free (ppath);
			ppath = g_strconcat (PLUGINS_DIR G_DIR_SEPARATOR_S, pname, NULL);
		}
		else
		{
			gchar *freeme = ppath;
			ppath = g_build_filename (ppath, pname, NULL);
			g_free (freeme);
		}
	}
	g_free (pname);


	GtkWidget *dialog = gtk_file_chooser_dialog_new (NULL,
		GTK_WINDOW (config_dialog), GTK_FILE_CHOOSER_ACTION_OPEN,
		GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
		GTK_STOCK_APPLY, GTK_RESPONSE_APPLY,
		GTK_STOCK_OK, GTK_RESPONSE_OK,
		NULL);

	e2_dialog_setup_chooser (dialog,
		_("choose plugin"),
		ppath,
		GTK_FILE_CHOOSER_ACTION_OPEN,
		TRUE,
		FALSE,
		GTK_RESPONSE_OK);

	if (ppath == NULL)
		gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), PLUGINS_DIR);
	else
		g_free (ppath);

	GtkFileFilter *filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (GTK_FILE_FILTER (filter), _("plugin"));
	gtk_file_filter_add_pattern (filter, "e2p*.so");
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dialog), filter);


	g_signal_connect (G_OBJECT (dialog), "response",
		G_CALLBACK (_e2_confdlg_plugpick_response_cb), data);

	e2_dialog_setup (dialog, config_dialog);
	gtk_widget_show (dialog);
}
