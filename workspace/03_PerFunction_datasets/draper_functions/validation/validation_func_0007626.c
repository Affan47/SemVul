o_line_draw(GSCHEM_TOPLEVEL *w_current, OBJECT *o_current)
{
  int x1, y1, x2, y2;

  if (o_current->line == NULL) {
    return;
  }

  if (!o_line_visible (w_current, o_current->line, &x1, &y1, &x2, &y2)) {
    return;
  }

  gschem_cairo_line (w_current, o_current->line_end,
                                o_current->line_width,
                                x1, y1, x2, y2);

  gschem_cairo_set_source_color (w_current,
                                 o_drawing_color (w_current, o_current));
  gschem_cairo_stroke (w_current, o_current->line_type,
                                  o_current->line_end,
                                  o_current->line_width,
                                  o_current->line_length,
                                  o_current->line_space);

  if (o_current->selected && w_current->draw_grips) {
    o_line_draw_grips (w_current, o_current);
  }
}
