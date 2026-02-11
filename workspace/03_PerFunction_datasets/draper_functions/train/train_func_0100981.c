gwy_graph_area_get_cursor(GwyGraphArea *area,
                          gdouble *x_cursor, gdouble *y_cursor)
{
    if (area->mouse_present) {
        *x_cursor = area->actual_cursor.x;
        *y_cursor = area->actual_cursor.y;

    }
    else {
        *x_cursor = 0;
        *y_cursor = 0;
    }
}
