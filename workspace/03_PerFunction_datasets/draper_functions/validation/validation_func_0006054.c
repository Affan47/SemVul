goo_canvas_line_dash_newv (gint    num_dashes,
                           double *dashes)
{
  GooCanvasLineDash *dash;

  dash = g_new (GooCanvasLineDash, 1);
  dash->ref_count = 1;
  dash->num_dashes = num_dashes;
  dash->dashes = dashes;
  dash->dash_offset = 0.0;

  return dash;
}
