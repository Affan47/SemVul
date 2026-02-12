queue_key_event (GSWindow    *window,
                 GdkEventKey *event)
{

        if (window->priv->key_events == NULL
            && (event->keyval == GDK_KEY_Return
                || event->keyval == GDK_KEY_KP_Enter
                || event->keyval == GDK_KEY_Escape
                || event->keyval == GDK_KEY_space)) {
                return;
        }


        if (g_list_length (window->priv->key_events) < MAX_QUEUED_EVENTS
            && event->keyval != GDK_KEY_Tab
            && event->keyval != GDK_KEY_Up
            && event->keyval != GDK_KEY_Down) {
                window->priv->key_events = g_list_prepend (window->priv->key_events,
                                                           gdk_event_copy ((GdkEvent *)event));
        }
}
