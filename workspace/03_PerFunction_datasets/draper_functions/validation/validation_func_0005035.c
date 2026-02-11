gwy_app_file_confirm_overwrite(GtkWidget *chooser)
{
    GtkWidget *dialog, *toplevel;
    gchar *filename_sys, *filename_utf8, *dirname_sys, *dirname_utf8,
          *fullname_sys;
    gint response;

    g_return_val_if_fail(gtk_file_chooser_get_action(GTK_FILE_CHOOSER(chooser))
                         == GTK_FILE_CHOOSER_ACTION_SAVE,
                         FALSE);
    fullname_sys = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
    if (!fullname_sys)
        return FALSE;
    if (!g_file_test(fullname_sys, G_FILE_TEST_EXISTS))
        return TRUE;

    filename_sys = g_path_get_basename(fullname_sys);
    dirname_sys = g_path_get_dirname(fullname_sys);
    filename_utf8 = g_filename_to_utf8(filename_sys, -1, NULL, NULL, NULL);
    dirname_utf8 = g_filename_to_utf8(dirname_sys, -1, NULL, NULL, NULL);

    toplevel = gtk_widget_get_toplevel(chooser);
    dialog = gtk_message_dialog_new(GTK_WINDOW(toplevel),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_YES_NO,
                                    _("File `%s' already exists.  Replace?"),
                                    filename_utf8);
    gtk_message_dialog_format_secondary_text
        (GTK_MESSAGE_DIALOG(dialog),
         _("The file already exists in `%s'.  "
           "Replacing it will overwrite its contents."),
         dirname_utf8);
    gtk_window_set_title(GTK_WINDOW(dialog), _("Replace File?"));

    g_free(fullname_sys);
    g_free(filename_sys);
    g_free(dirname_sys);
    g_free(filename_utf8);
    g_free(dirname_utf8);

    response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return response == GTK_RESPONSE_YES;
}
