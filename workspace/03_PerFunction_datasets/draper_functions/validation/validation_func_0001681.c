c_fmt_dialog_set_sensitive (CFormatState *state)
{
	gboolean ok = (state->editor.style != NULL && state->homogeneous);
	GnmParsePos pp;
	GtkTreeIter iter;
	gboolean not_empty, selected;

	not_empty = gtk_tree_model_get_iter_first
		(GTK_TREE_MODEL (state->model), &iter);
	selected = gtk_tree_selection_get_selected
		(state->selection, NULL, NULL);

	gtk_widget_set_sensitive (GTK_WIDGET (state->clear), not_empty);

	gtk_widget_set_sensitive (GTK_WIDGET (state->remove),
				  state->homogeneous && selected);
	gtk_widget_set_sensitive (GTK_WIDGET (state->expand),
				  (!state->homogeneous) && selected);

	parse_pos_init_editpos (&pp, state->sv);

	if (ok && gtk_widget_get_sensitive (state->editor.expr_x)) {
		GnmExprTop const *texpr = gnm_expr_entry_parse (GNM_EXPR_ENTRY (state->editor.expr_x), &pp,
								NULL, FALSE,
								GNM_EXPR_PARSE_UNKNOWN_NAMES_ARE_STRINGS);
		ok = (texpr != NULL);
		if (texpr)
			gnm_expr_top_unref (texpr);
	}
	if (ok && gtk_widget_get_sensitive (state->editor.expr_y)) {
		GnmExprTop const *texpr = gnm_expr_entry_parse (GNM_EXPR_ENTRY (state->editor.expr_y), &pp,
								NULL, FALSE,
								GNM_EXPR_PARSE_UNKNOWN_NAMES_ARE_STRINGS);
		ok = (texpr != NULL);
		if (texpr)
			gnm_expr_top_unref (texpr);
	}

	gtk_widget_set_sensitive (state->editor.add_button, ok);
	gtk_widget_set_sensitive (state->editor.replace_button, ok && selected);
	gtk_widget_set_sensitive (state->editor.copy_button, selected && state->homogeneous);
}
