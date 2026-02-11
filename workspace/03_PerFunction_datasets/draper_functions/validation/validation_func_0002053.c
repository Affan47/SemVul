gnc_verify_dialog(GtkWidget *parent, gboolean yes_is_default,
                  const gchar *format, ...)
{
    GtkWidget *dialog;
    gchar *buffer;
    gint result;
    va_list args;

    if (parent == NULL)
        parent = gnc_ui_get_toplevel();

    va_start(args, format);
    buffer = g_strdup_vprintf(format, args);
    dialog = gtk_message_dialog_new (GTK_WINDOW(parent),
                                     GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_QUESTION,
                                     GTK_BUTTONS_YES_NO,
                                     "%s",
                                     buffer);
    g_free(buffer);
    va_end(args);

    if (parent == NULL)
        gtk_window_set_skip_taskbar_hint(GTK_WINDOW(dialog), FALSE);

    gtk_dialog_set_default_response(GTK_DIALOG(dialog),
                                    (yes_is_default ? GTK_RESPONSE_YES : GTK_RESPONSE_NO));
    result = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy (dialog);
    return (result == GTK_RESPONSE_YES);
}
