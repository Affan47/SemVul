proxy_action_chagned_cb( GtkRadioAction* action, GtkRadioAction* current, gpointer user_data )
{
    (void)current;
    if ( gtk_toggle_action_get_active( GTK_TOGGLE_ACTION(action) ) ) {
        EgeSelectOneAction* act = EGE_SELECT_ONE_ACTION(user_data);
        gint newActive = gtk_radio_action_get_current_value( action );
        if ( newActive != act->private_data->active ) {
            g_object_set( G_OBJECT(act), "active", newActive, NULL );
        }
    }
}
