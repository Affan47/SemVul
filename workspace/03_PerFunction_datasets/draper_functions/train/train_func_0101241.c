gwy_graph_area_draw_zoom(GdkDrawable *drawable,
                         GdkGC *gc,
                         GwyGraphArea *area)
{
    gint xmin, ymin, xmax, ymax, n_of_zooms;
    gdouble selection_zoomdata[4];

    n_of_zooms = gwy_selection_get_data(area->zoomdata, NULL);

    if (n_of_zooms != 1)
        return;

    gwy_selection_get_object(area->zoomdata, 0, selection_zoomdata);

    if (selection_zoomdata[2] == 0 || selection_zoomdata[3] == 0) return;
    gdk_gc_set_function(gc, GDK_INVERT);

    if (selection_zoomdata[2] < 0) {
        xmin = data_to_scr_x(GTK_WIDGET(area), selection_zoomdata[0]
                             + selection_zoomdata[2]);
        xmax = data_to_scr_x(GTK_WIDGET(area), selection_zoomdata[0]);
    }
    else {
        xmin = data_to_scr_x(GTK_WIDGET(area), selection_zoomdata[0]);
        xmax = data_to_scr_x(GTK_WIDGET(area), selection_zoomdata[0]
                             + selection_zoomdata[2]);
    }

    if (selection_zoomdata[3] > 0) {
        ymin = data_to_scr_y(GTK_WIDGET(area), selection_zoomdata[1]
                             + selection_zoomdata[3]);
        ymax = data_to_scr_y(GTK_WIDGET(area), selection_zoomdata[1]);
    }
    else {
        ymin = data_to_scr_y(GTK_WIDGET(area), selection_zoomdata[1]);
        ymax = data_to_scr_y(GTK_WIDGET(area), selection_zoomdata[1]
                             + selection_zoomdata[3]);
    }

    gdk_draw_rectangle(drawable, area->gc, 0,
                       xmin,
                       ymin,
                       xmax - xmin,
                       ymax - ymin);

    gdk_gc_set_function(area->gc, GDK_COPY);
}
