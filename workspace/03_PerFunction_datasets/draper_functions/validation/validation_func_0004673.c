tmg_stop     (GtkWidget *widget, gpointer data)
{
    GtkSatModule *mod = GTK_SAT_MODULE (data);

    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget))) {

        sat_log_log (SAT_LOG_LEVEL_DEBUG, __FUNCTION__);


        mod->throttle = 0;

    }

}
