update_rect_at_mouse_pos(void)
{
  int canvas_x, canvas_y;

  if (!rbutton_down) {
    return;
  }


  gdk_window_get_pointer(map_canvas->window, &canvas_x, &canvas_y, NULL);
  update_selection_rectangle(canvas_x, canvas_y);
}
