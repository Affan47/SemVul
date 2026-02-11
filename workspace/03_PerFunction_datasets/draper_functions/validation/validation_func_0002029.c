pdfscreenshot_window_selected(GtkWidget *grab_window,
                  GdkEventButton *event,
                  GtkButton *button)
{

    gdk_pointer_ungrab(event->time);


    gtk_button_released(GTK_BUTTON(button));


    Window selected_window = None;
    int dummy;
    unsigned int dummyU;
    Window dummyW;
    XQueryPointer(gdk_x11_get_default_xdisplay(),
        gdk_x11_get_default_root_xwindow(),
        &dummyW, &selected_window, &dummy, &dummy, &dummy, &dummy, &dummyU);


    selected_window = Find_Client(gdk_x11_get_default_xdisplay(),
        gdk_x11_get_default_root_xwindow(),
        selected_window);

    if (selected_window != None) {

        XTextProperty supported;
        XGetTextProperty(gdk_x11_get_default_xdisplay(),
            selected_window,
            &supported,
            gdk_x11_atom_to_xatom(pdfscreenshot_atom));
        if (supported.value != NULL) {


            XClientMessageEvent xevent;
            xevent.type = ClientMessage;
            xevent.message_type = gdk_x11_atom_to_xatom(pdfscreenshot_atom);
            xevent.format = 32;
            xevent.window  = selected_window;
            XSendEvent(gdk_x11_get_default_xdisplay(), selected_window, 0, 0, (XEvent *)&xevent);
            return TRUE;
        }
    }


    GtkWidget *dialog = gtk_message_dialog_new (main_window,
         GTK_DIALOG_DESTROY_WITH_PARENT,
         GTK_MESSAGE_ERROR,
         GTK_BUTTONS_CLOSE,
         "The selected window does not support taking vector screenshots. Is it "
         "a gtk-3 based application, and did you load the gtk-vector-screenshot "
         "module?");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);

    return TRUE;
}
