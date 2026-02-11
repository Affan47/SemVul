draw_preview (glMiniLabelPreview *this,
              cairo_t            *cr)
{
        GtkAllocation           allocation;
        GtkStyle               *style;
        gdouble                 w, h;
        guint                   fill_color, line_color, shadow_color;
        const lglTemplateFrame *frame;
        gdouble                 w_label, h_label;
        gdouble                 scale;


        gtk_widget_get_allocation (GTK_WIDGET (this), &allocation);
        w = allocation.width;
        h = allocation.height;


        style = gtk_widget_get_style (GTK_WIDGET (this));
        if ( gtk_widget_is_sensitive (GTK_WIDGET (this)) )
        {
                fill_color   = gl_color_from_gdk_color (&style->light[GTK_STATE_NORMAL]);
                line_color   = gl_color_from_gdk_color (&style->fg[GTK_STATE_NORMAL]);
                shadow_color = gl_color_from_gdk_color (&style->dark[GTK_STATE_NORMAL]);
        }
        else
        {
                fill_color   = GL_COLOR_NONE;
                line_color   = gl_color_from_gdk_color (&style->fg[GTK_STATE_INSENSITIVE]);
                shadow_color = GL_COLOR_NONE;
        }


        if (this->priv->template == NULL)
        {
                return;
        }

        frame = (lglTemplateFrame *)this->priv->template->frames->data;

        if (this->priv->rotate_flag)
        {
                lgl_template_frame_get_size (frame, &h_label, &w_label);
        }
        else
        {
                lgl_template_frame_get_size (frame, &w_label, &h_label);
        }

        scale = MIN( (w - 2*MARGIN - 2*SHADOW_OFFSET)/w_label,
                     (h - 2*MARGIN - 2*SHADOW_OFFSET)/h_label );


        cairo_translate (cr, w/2.0, h/2.0);
        cairo_scale (cr, scale, scale);
        cairo_translate (cr, -w_label/2.0, -h_label/2.0);


        cairo_save (cr);
        cairo_translate (cr, SHADOW_OFFSET/scale, SHADOW_OFFSET/scale);
        gl_cairo_label_path (cr, this->priv->template, this->priv->rotate_flag, FALSE);

        cairo_set_source_rgba (cr, GL_COLOR_RGBA_ARGS (shadow_color));
        cairo_fill (cr);
        cairo_restore (cr);


        gl_cairo_label_path (cr, this->priv->template, this->priv->rotate_flag, FALSE);

        cairo_set_source_rgba (cr, GL_COLOR_RGBA_ARGS (fill_color));
        cairo_fill_preserve (cr);

        cairo_set_line_width (cr, 1.0/scale);
        cairo_set_source_rgba (cr, GL_COLOR_RGBA_ARGS (line_color));
        cairo_stroke (cr);

}
