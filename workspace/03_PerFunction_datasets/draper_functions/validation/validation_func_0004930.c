policy_view_create(toplevel_t * top, sediffx_policy_e which)
{
	policy_view_t *view;
	GtkTextTag *mono_tag;
	int error = 0;

	if ((view = calloc(1, sizeof(*view))) == NULL) {
		error = errno;
		goto cleanup;
	}
	view->top = top;
	view->which = which;

	view->xml = glade_get_widget_tree(GTK_WIDGET(toplevel_get_window(view->top)));
	view->stats = gtk_text_buffer_new(NULL);
	view->source = gtk_text_buffer_new(NULL);
	mono_tag = gtk_text_buffer_create_tag(view->source, "mono-tag",
					      "style", PANGO_STYLE_NORMAL,
					      "weight", PANGO_WEIGHT_NORMAL, "family", "monospace", NULL);

	view->stats_view = GTK_TEXT_VIEW(glade_xml_get_widget(view->xml, policy_view_widget_names[view->which][0]));
	view->source_view = GTK_TEXT_VIEW(glade_xml_get_widget(view->xml, policy_view_widget_names[view->which][1]));
	assert(view->stats_view != NULL && view->source_view != NULL);
	gtk_text_view_set_buffer(view->stats_view, view->stats);
	gtk_text_view_set_buffer(view->source_view, view->source);

	view->notebook = GTK_NOTEBOOK(glade_xml_get_widget(view->xml, policy_view_widget_names[view->which][2]));
	view->line_number = GTK_LABEL(glade_xml_get_widget(view->xml, "toplevel line label"));
	assert(view->notebook != NULL && view->line_number != NULL);
	g_signal_connect_after(G_OBJECT(view->notebook), "event-after", G_CALLBACK(policy_view_notebook_on_event_after), view);

      cleanup:
	if (error != 0) {
		policy_view_destroy(&view);
		errno = error;
		return NULL;
	}
	return view;
}
