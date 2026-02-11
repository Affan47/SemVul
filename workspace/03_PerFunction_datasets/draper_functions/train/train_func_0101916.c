search_files_editor_loaded (SearchFiles* sf, IAnjutaEditor* editor)
{
	search_box_set_search_string(sf->priv->search_box,
	                             sf->priv->last_search_string);
	if (sf->priv->last_replace_string)
	{
		search_box_set_replace_string(sf->priv->search_box,
		                              sf->priv->last_replace_string);
		search_box_set_replace(sf->priv->search_box,
		                       TRUE);
	}
	else
	{
		search_box_set_replace(sf->priv->search_box,
		                       FALSE);
	}
	search_box_toggle_case_sensitive(sf->priv->search_box,
	                                 sf->priv->case_sensitive);
	search_box_toggle_highlight(sf->priv->search_box,
	                            TRUE);
	search_box_toggle_regex(sf->priv->search_box,
	                        sf->priv->regex);
	search_box_highlight_all(sf->priv->search_box);
	search_box_incremental_search(sf->priv->search_box, TRUE, TRUE, FALSE);

	gtk_widget_show (GTK_WIDGET(sf->priv->search_box));
}
