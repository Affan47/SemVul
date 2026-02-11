gucharmap_chartable_set_active_cell (GucharmapChartable *chartable,
                                     int cell)
{
  GtkWidget *widget = GTK_WIDGET (chartable);
  GucharmapChartablePrivate *priv = chartable->priv;
  int old_active_cell, old_page_first_cell;

  if (cell == priv->active_cell)
    return;

  if (cell < 0)
    cell = 0;
  else if (cell > priv->last_cell)
    cell = priv->last_cell;

  old_active_cell = priv->active_cell;
  old_page_first_cell = priv->page_first_cell;

  priv->active_cell = cell;

  if (cell < priv->page_first_cell || cell >= priv->page_first_cell + priv->page_size)
    {
      int old_row = old_active_cell / priv->cols;
      int new_row = cell / priv->cols;
      int new_page_first_cell = old_page_first_cell + (new_row - old_row) * priv->cols;
      int last_page_first_cell = (priv->last_cell / priv->cols - priv->rows + 1) * priv->cols;

      priv->page_first_cell = CLAMP (new_page_first_cell, 0, last_page_first_cell);

      if (priv->vadjustment)
        gtk_adjustment_set_value (priv->vadjustment, priv->page_first_cell / priv->cols);
    }
  else if (gtk_widget_get_realized (widget)) {
    expose_cell (chartable, old_active_cell);
    expose_cell (chartable, cell);
  }

  g_object_notify (G_OBJECT (chartable), "active-character");

  update_zoom_window (chartable);
  place_zoom_window_on_active_cell (chartable);
}
