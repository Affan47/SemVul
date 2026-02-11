sync_sensitivity(GtkWidget *master,
                 G_GNUC_UNUSED GtkStateType state,
                 GtkWidget *slave)
{
    gtk_widget_set_sensitive(slave, GTK_WIDGET_IS_SENSITIVE(master));
}
