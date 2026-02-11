exo_icon_view_start_rubberbanding (ExoIconView  *icon_view,
                                   gint          x,
                                   gint          y)
{
  const GdkColor *background_color;
  GdkColor       *color;
  guchar          alpha;
  gpointer        drag_data;
  GList          *items;
  GtkStyle       *style;


  exo_icon_view_stop_rubberbanding (icon_view);

  for (items = icon_view->priv->items; items; items = items->next)
    {
      ExoIconViewItem *item = items->data;
      item->selected_before_rubberbanding = item->selected;
    }

  icon_view->priv->rubberband_x_1 = x;
  icon_view->priv->rubberband_y_1 = y;
  icon_view->priv->rubberband_x2 = x;
  icon_view->priv->rubberband_y2 = y;

  icon_view->priv->doing_rubberband = TRUE;


  gtk_widget_style_get (GTK_WIDGET (icon_view), "selection-box-color", &color, NULL);
  style = gtk_widget_get_style (GTK_WIDGET (icon_view));
  if (G_LIKELY (color == NULL))
    color = gdk_color_copy (&style->base[GTK_STATE_SELECTED]);


  icon_view->priv->rubberband_border_color = color;


  gtk_widget_style_get (GTK_WIDGET (icon_view), "selection-box-color", &color, "selection-box-alpha", &alpha, NULL);
  if (G_LIKELY (color == NULL))
    color = gdk_color_copy (&style->base[GTK_STATE_SELECTED]);


  background_color = &style->base[GTK_STATE_NORMAL];
  color->red = ((color->red * (alpha / 255.0)) + (background_color->red * (255.0 - alpha / 255.0)));
  color->green = ((color->green * (alpha / 255.0)) + (background_color->green * (255.0 - alpha / 255.0)));
  color->blue = ((color->blue * (alpha / 255.0)) + (background_color->blue * (255.0 - alpha / 255.0)));


  icon_view->priv->rubberband_fill_color = color;

  gtk_grab_add (GTK_WIDGET (icon_view));


  drag_data = g_object_get_data (G_OBJECT (icon_view), I_("gtk-site-data"));
  if (G_LIKELY (drag_data != NULL))
    {
      g_signal_handlers_block_matched (G_OBJECT (icon_view),
                                       G_SIGNAL_MATCH_DATA,
                                       0, 0, NULL, NULL,
                                       drag_data);
    }
}
