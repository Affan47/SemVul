internal_generic_eventhandler(plugin_event_t *event) {

    lcd_t *lcd = (lcd_t*) event->lcd;

    switch (event->event)
    {
        case G15_EVENT_KEYPRESS: {
            if(lcd->g15plugin->plugin_handle){

            }
        }
        break;
        case G15_EVENT_VISIBILITY_CHANGED:
          break;
        default:
          break;
    }
    return G15_PLUGIN_OK;
}
