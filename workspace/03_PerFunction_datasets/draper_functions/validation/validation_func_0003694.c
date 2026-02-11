gui_widget_set_active( GuiWidget *widget, int active )
{
    int type;
    if ( widget->active == active ) return;
    widget->active = active;
    type = (active)?GUI_ACTIVATED:GUI_DEACTIVATED;
    widget->default_event_handler(
        widget, gui_event_get_simple( type ) );
    gui_widget_call_user_event_handler(
        widget, gui_event_get_simple( type ) );
}
