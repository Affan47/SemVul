exo_icon_view_layout_cols (ExoIconView *icon_view,
                           gint         item_height,
                           gint        *x,
                           gint        *maximum_height,
                           gint         max_rows)
{
  GList *icons = icon_view->priv->items;
  GList *items;
  gboolean rtl;
  gint   col = 0;
  gint   rows = 0;
  gint   shift;

  rtl = (gtk_widget_get_direction (GTK_WIDGET (icon_view)) == GTK_TEXT_DIR_RTL);

  shift = icon_view->priv->margin;
  *x = shift;

  do
    {
      items = icons;
      icons = exo_icon_view_layout_single_col (icon_view, icons,
                                               item_height, col,
                                               &shift, maximum_height, max_rows);

      if (rtl)
      {
          GList *items2;
          ExoIconViewItem *item;
          gint i;


          shift -= icon_view->priv->margin;
          *x += shift;

          if (items) for (items2 = icon_view->priv->items; items2 != items; items2 = items2->next)
          {
              item = EXO_ICON_VIEW_ITEM (items2->data);

              item->area.x += shift;
              for (i = 0; i < icon_view->priv->n_cells; i++)
                  item->box[i].x += shift;
          }

          shift = icon_view->priv->margin;
      }
      else
          *x = shift;

      if (G_UNLIKELY (col == 0))
        {
          for (items = icon_view->priv->items, rows = 0; items != icons; items = items->next, ++rows)
            ;
        }

      col++;
    }
  while (icons != NULL);

  *x += icon_view->priv->margin;
  icon_view->priv->cols = col;

  return rows;
}
