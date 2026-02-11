gtk_plot_canvas_child_button_release(GtkPlotCanvas *canvas, GtkPlotCanvasChild *child)
{
  gdouble new_x, new_y, new_width, new_height;
  double dx, dy;
  gdouble x1, x2, y1, y2;

  gtk_plot_canvas_get_position(canvas,
                               canvas->drag_area.width,
                               canvas->drag_area.height,
                               &new_width, &new_height);

  gtk_plot_canvas_get_position(canvas,
                               canvas->drag_area.x,
                               canvas->drag_area.y,
                               &new_x, &new_y);

  gtk_plot_canvas_get_position(canvas,
                               canvas->drag_area.x - child->drag_area.x,
                               canvas->drag_area.y - child->drag_area.y,
                               &dx, &dy);

  x1 = MIN(child->rx1, child->rx2);
  y1 = MIN(child->ry1, child->ry2);
  x2 = MAX(child->rx1, child->rx2);
  y2 = MAX(child->ry1, child->ry2);
  x1 += dx;
  y1 += dy;
  x2 = x1 + new_width;
  y2 = y1 + new_height;

  gtk_plot_canvas_child_move_resize(canvas, child, x1, y1, x2, y2);
  child->drag_area = canvas->drag_area;
}
