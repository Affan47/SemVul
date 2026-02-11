pidgin_cell_renderer_expander_render(GtkCellRenderer *cell,
                           GdkWindow       *window,
                           GtkWidget       *widget,
                           GdkRectangle    *background_area,
                           GdkRectangle    *cell_area,
                           GdkRectangle    *expose_area,
                           guint            flags)
{
    PidginCellRendererExpander *cellexpander = (PidginCellRendererExpander *) cell;
    gboolean set;
    gint width, height;
    GtkStateType state;

    if (!cellexpander->is_expander)
        return;

    width = cell_area->width;
    height = cell_area->height;

    if (!cell->sensitive)
        state = GTK_STATE_INSENSITIVE;
    else if (flags & GTK_CELL_RENDERER_PRELIT)
        state = GTK_STATE_PRELIGHT;
    else if (GTK_WIDGET_HAS_FOCUS (widget) && flags & GTK_CELL_RENDERER_SELECTED)
        state = GTK_STATE_ACTIVE;
    else
        state = GTK_STATE_NORMAL;

    width -= cell->xpad*2;
    height -= cell->ypad*2;

    gtk_paint_expander (widget->style,
                window, state,
                NULL, widget, "treeview",
                cell_area->x + cell->xpad + (width / 2),
                cell_area->y + cell->ypad + (height / 2),
                cell->is_expanded ? GTK_EXPANDER_EXPANDED : GTK_EXPANDER_COLLAPSED);


    g_object_get(cellexpander, "cell-background-set", &set, NULL);
    if (cell->is_expanded && !set)
        gtk_paint_hline (widget->style, window, state, NULL, widget, NULL, 0,
                 widget->allocation.width, cell_area->y + cell_area->height);
}
