add_prompt (GtkWidget *vbox, const char *prompt_text, gboolean pack_at_start)
{
	GtkWidget *prompt;

	prompt = gtk_label_new (prompt_text);
   	gtk_label_set_justify (GTK_LABEL (prompt), GTK_JUSTIFY_LEFT);
	gtk_label_set_line_wrap (GTK_LABEL (prompt), TRUE);
	gtk_widget_show (prompt);
	if (pack_at_start) {
		gtk_box_pack_start (GTK_BOX (vbox), prompt, FALSE, FALSE, 0);
	} else {
		gtk_box_pack_end (GTK_BOX (vbox), prompt, FALSE, FALSE, 0);
	}
}
