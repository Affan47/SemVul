goo_canvas_query_tooltip (GtkWidget  *widget,
			  gint        x,
			  gint        y,
			  gboolean    keyboard_tip,
			  GtkTooltip *tooltip)
{
  GooCanvas *canvas = (GooCanvas*) widget;
  GooCanvasItem *item = canvas->pointer_item, *parent;
  gdouble item_x = x, item_y = y;
  gboolean tip_set = FALSE, has_transform;
  cairo_matrix_t transform;

  if (!item)
    return FALSE;


  goo_canvas_convert_from_pixels (canvas, &item_x, &item_y);
  goo_canvas_convert_to_item_space (canvas, item, &item_x, &item_y);

  for (;;)
    {
      g_signal_emit_by_name (item, "query-tooltip", item_x, item_y,
			     keyboard_tip, tooltip, &tip_set);
      if (tip_set)
	return TRUE;

      parent = goo_canvas_item_get_parent (item);
      if (!parent)
	break;


      has_transform = goo_canvas_item_get_transform_for_child (parent, item,
							       &transform);
      if (has_transform)
	cairo_matrix_transform_point (&transform, &item_x, &item_y);

      item = parent;
    }


  return GTK_WIDGET_CLASS (goo_canvas_parent_class)->query_tooltip (widget, x, y, keyboard_tip, tooltip);
}
