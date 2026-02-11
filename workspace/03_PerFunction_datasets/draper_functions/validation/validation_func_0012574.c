cb_dialog_so_styled_response (GtkWidget *dialog,
			      gint response_id, DialogSOStyled *pref)
{
	if (response_id == GTK_RESPONSE_HELP)
		return;
	if (response_id == GTK_RESPONSE_OK) {
		cmd_object_format (WORKBOOK_CONTROL (pref->wbcg),
				   SHEET_OBJECT (pref->so), pref->orig_style,
				   pref->orig_text, pref->orig_attributes);
		g_object_unref (pref->orig_style);
		pref->orig_style = NULL;
		g_free (pref->orig_text);
		pref->orig_text = NULL;
		pango_attr_list_unref (pref->orig_attributes);
		pref->orig_attributes = NULL;
	}
	gtk_widget_destroy (dialog);
}
