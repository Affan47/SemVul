status_icon_activate_cb (GtkStatusIcon *status_icon, gpointer data)
{
        GsdXrandrManager *manager = GSD_XRANDR_MANAGER (data);


        status_icon_popup_menu (manager, 0, gtk_get_current_event_time ());
}
