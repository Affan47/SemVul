on_select_key_file_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *dialog;
    const gchar *fpm_directory;

    dialog = gtk_file_chooser_dialog_new (_("Select Key File"),
    				      GTK_WINDOW(glb_win_misc),
    				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);

    fpm_directory = g_get_home_dir();
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), fpm_directory);

    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
	char *filename;

        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
	GtkComboBox *combo_box;

        combo_box = GTK_COMBO_BOX(lookup_widget(gtk_widget_get_toplevel(GTK_WIDGET(button)), "key_file_combo"));
	gtk_combo_box_insert_text(combo_box, 1, filename);
        gtk_combo_box_set_active(combo_box, 1);

	g_free (filename);
    }
    gtk_widget_destroy (dialog);
}
