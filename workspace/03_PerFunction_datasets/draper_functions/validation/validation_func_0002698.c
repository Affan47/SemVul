ario_connection_widget_local_changed_cb (GtkWidget *widget,
                                         ArioConnectionWidget *connection_widget)
{
        ARIO_LOG_FUNCTION_START;
        gboolean local;


        local = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (connection_widget->priv->local_checkbutton));
        connection_widget->priv->current_profile->local = local;
        if (local) {
                gtk_widget_show (connection_widget->priv->musicdir_hbox);
                gtk_widget_show (connection_widget->priv->musicdir_label);
        } else {
                gtk_widget_hide (connection_widget->priv->musicdir_hbox);
                gtk_widget_hide (connection_widget->priv->musicdir_label);
        }
}
