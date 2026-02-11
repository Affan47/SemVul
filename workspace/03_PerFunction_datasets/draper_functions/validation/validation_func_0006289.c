onbuttondown(GtkWidget *widget, GdkEventButton *event, void *data)
{
    if (event->button == 1)
        gli_input_handle_click(event->x, event->y);
    else if (event->button == 2)
        winclipreceive(PRIMARY);
}
