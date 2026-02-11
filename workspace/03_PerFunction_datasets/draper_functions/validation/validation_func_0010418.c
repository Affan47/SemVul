stpui_curve_draw (StpuiCurve *c, gint width, gint height)
{
  GtkStateType state;
  GtkStyle *style;
  gint i;

  if (!c->pixmap)
    return;

  if (c->height != height || c->num_points != width)
    stpui_curve_interpolate (c, width, height);

  state = GTK_STATE_NORMAL;
  if (!GTK_WIDGET_IS_SENSITIVE (GTK_WIDGET (c)))
    state = GTK_STATE_INSENSITIVE;

  style = GTK_WIDGET (c)->style;


  gtk_paint_flat_box (style, c->pixmap, GTK_STATE_NORMAL, GTK_SHADOW_NONE,
		      NULL, GTK_WIDGET (c), "curve_bg",
		      0, 0, width + RADIUS * 2, height + RADIUS * 2);

  for (i = 0; i < 5; i++)
    {
      gdk_draw_line (c->pixmap, style->dark_gc[state],
		     RADIUS, i * (height / 4.0) + RADIUS,
		     width + RADIUS, i * (height / 4.0) + RADIUS);
      gdk_draw_line (c->pixmap, style->dark_gc[state],
		     i * (width / 4.0) + RADIUS, RADIUS,
		     i * (width / 4.0) + RADIUS, height + RADIUS);
    }

  gdk_draw_points (c->pixmap, style->fg_gc[state], c->point, c->num_points);
  if (c->curve_type != STPUI_CURVE_TYPE_FREE)
    for (i = 0; i < c->num_ctlpoints; ++i)
      {
	gint x, y;

	if (c->ctlpoint[i][0] < c->min_x)
	  continue;

	x = project (c->ctlpoint[i][0], c->min_x, c->max_x,
		     width);
	y = height -
	  project (c->ctlpoint[i][1], c->min_y, c->max_y,
		   height);


	gdk_draw_arc (c->pixmap, style->fg_gc[state], TRUE, x, y,
		      RADIUS * 2, RADIUS*2, 0, 360*64);
      }
  gdk_draw_drawable (GTK_WIDGET (c)->window, style->fg_gc[state], c->pixmap,
		     0, 0, 0, 0, width + RADIUS * 2, height + RADIUS * 2);
}
