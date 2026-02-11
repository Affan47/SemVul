stop_test_cb (GtkWidget *widget, gpointer user_data) {

GtkWidget *info_dialog = NULL;
gint response = -1;

    GUI *appGUI = (GUI *)user_data;

    info_dialog = gtk_message_dialog_new_with_markup (GTK_WINDOW(appGUI->main_window),
                                                      GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL,
                                                      GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO,
                                                      _("Test is in progress... Abort?"));

    gtk_window_set_title (GTK_WINDOW(info_dialog), _("Question"));
    gtk_widget_show (info_dialog);

    response = gtk_dialog_run(GTK_DIALOG(info_dialog));
    gtk_widget_destroy(info_dialog);

    if (response == GTK_RESPONSE_YES) {
        if (config.repeat_mode == REPEAT_ALL) {
            test_info (appGUI);
        } else {
            gui_disable_test (appGUI);
        }
    }
}
