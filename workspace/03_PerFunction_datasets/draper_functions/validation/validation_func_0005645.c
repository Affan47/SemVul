ladish_run_load_project_dialog(ladish_room_proxy_handle room)
{
  GtkFileFilter * filter;
  GtkWidget * dialog;
  char * filename;

  dialog = gtk_file_chooser_dialog_new(
    _("Load project"),
    NULL,
    GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
    GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
    GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
    NULL);

  gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(dialog), FALSE);

  filter = gtk_file_filter_new();
  gtk_file_filter_add_custom(filter, GTK_FILE_FILTER_FILENAME, reject_filter, dialog, NULL);
  gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), filter);

  g_signal_connect(G_OBJECT(dialog), "current-folder-changed", G_CALLBACK(dir_changed), dialog);

loop:
  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
  {
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

    if (!is_project_dir(filename))
    {
      GtkWidget * dialog;
      dialog = get_gtk_builder_widget("error_dialog");
      gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(dialog), _("<b><big>Not a project dir</big></b>"));
      gtk_message_dialog_format_secondary_markup(GTK_MESSAGE_DIALOG(dialog), "%s", filename);
      gtk_widget_show(dialog);
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_hide(dialog);
      goto loop;
    }


    log_info("Loading project from '%s'", filename);
    if (!ladish_room_proxy_load_project(room, filename))
    {
      log_error("ladish_room_proxy_load_project() failed.");
    }

    g_free(filename);


  }
  gtk_widget_destroy(dialog);
  return;
}
