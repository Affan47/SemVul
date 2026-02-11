draw_swatch (glColorSwatch *this,
             cairo_t       *cr)
{
        GtkAllocation  allocation;
        GtkStyle      *style;
        gdouble        w, h;
        guint          fill_color, line_color;


        cairo_set_antialias (cr, CAIRO_ANTIALIAS_NONE);


        gtk_widget_get_allocation (GTK_WIDGET (this), &allocation);
        w = allocation.width;
        h = allocation.height;


        style = gtk_widget_get_style (GTK_WIDGET (this));
        if ( gtk_widget_is_sensitive (GTK_WIDGET (this)) )
        {
                fill_color = this->priv->color;
                line_color = gl_color_from_gdk_color (&style->fg[GTK_STATE_NORMAL]);
        }
        else
        {
                fill_color = GL_COLOR_NONE;
                line_color = gl_color_from_gdk_color (&style->fg[GTK_STATE_INSENSITIVE]);
        }

        cairo_rectangle( cr, 1, 1, w-2, h-2 );

        cairo_set_source_rgba (cr, GL_COLOR_RGBA_ARGS (fill_color));
        cairo_fill_preserve( cr );

        cairo_set_source_rgb (cr, GL_COLOR_RGB_ARGS (line_color));
        cairo_set_line_width (cr, 1.0);
        cairo_stroke (cr);
}
