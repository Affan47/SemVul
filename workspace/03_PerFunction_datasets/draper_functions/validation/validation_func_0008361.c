egg_histogram_view_button_press (GtkWidget *widget,
                                 GdkEventButton *event)
{
    EggHistogramView *view;
    EggHistogramViewPrivate *priv;
    GtkAllocation allocation;

    view = EGG_HISTOGRAM_VIEW (widget);
    priv = view->priv;
    gtk_widget_get_allocation (widget, &allocation);

    if (is_on_border (priv, &allocation, event->x)) {
        gdouble coord;

        priv->grabbing = TRUE;
        coord = screen_to_histogram_coordinate (priv, &allocation, event->x);

        if (ABS (coord - priv->min_value < 6))
            priv->grabbed = GRAB_MIN;
        else if (ABS (coord - priv->max_value < 6))
            priv->grabbed = GRAB_MAX;

        set_grab_value (view, coord);
        set_cursor_type (view, GDK_FLEUR);
    }

    return TRUE;
}
