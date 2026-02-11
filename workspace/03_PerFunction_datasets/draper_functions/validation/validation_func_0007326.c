xim_forward_event (XIMS xims, IMForwardEventStruct *call_data)
{
    X11IC *x11ic;
    XKeyEvent *xevent;
    GdkEventKey event;
    gboolean retval;

    LOG (1, "XIM_FORWARD_EVENT ic=%d connect_id=%d",
                call_data->icid, call_data->connect_id);

    x11ic = (X11IC *) g_hash_table_lookup (_x11_ic_table,
                                           GINT_TO_POINTER ((gint) call_data->icid));
    g_return_val_if_fail (x11ic != NULL, 0);

    xevent = (XKeyEvent*) &(call_data->event);

    translate_key_event (gdk_display_get_default (),
        (GdkEvent *)&event, (XEvent *)xevent);

    event.send_event = xevent->send_event;
    event.window = NULL;

    if (event.type == GDK_KEY_RELEASE) {
        event.state |= IBUS_RELEASE_MASK;
    }

    if (_use_sync_mode) {
        retval = ibus_input_context_process_key_event (
                                      x11ic->context,
                                      event.keyval,
                                      event.hardware_keycode - 8,
                                      event.state);
        if (retval) {
            if (! x11ic->has_preedit_area) {
                _xim_set_cursor_location (x11ic);
            }
            return 1;
        }

        IMForwardEventStruct fe;
        memset (&fe, 0, sizeof (fe));

        fe.major_code = XIM_FORWARD_EVENT;
        fe.icid = x11ic->icid;
        fe.connect_id = x11ic->connect_id;
        fe.sync_bit = 0;
        fe.serial_number = 0L;
        fe.event = call_data->event;

        IMForwardEvent (_xims, (XPointer) &fe);

        retval = 1;
    }
    else {
        IMForwardEventStruct *pfe;

        pfe = g_slice_new0 (IMForwardEventStruct);
        pfe->major_code = XIM_FORWARD_EVENT;
        pfe->icid = x11ic->icid;
        pfe->connect_id = x11ic->connect_id;
        pfe->sync_bit = 0;
        pfe->serial_number = 0L;
        pfe->event = call_data->event;

        ibus_input_context_process_key_event_async (
                                      x11ic->context,
                                      event.keyval,
                                      event.hardware_keycode - 8,
                                      event.state,
                                      -1,
                                      NULL,
                                      _process_key_event_done,
                                      pfe);
        retval = 1;
    }
    return retval;
}
