draw(int X, int Y, int W, int H) {
  Fl_Color box_color = type()==FL_ROUND_CLOCK ? FL_GRAY : color();
  Fl_Color shadow_color = fl_color_average(box_color, FL_BLACK, 0.5);
  draw_box(box(), X, Y, W, H, box_color);
  fl_push_matrix();
  fl_translate(X+W/2.0-.5, Y+H/2.0-.5);
  fl_scale((W-1)/28.0, (H-1)/28.0);
  if (type() == FL_ROUND_CLOCK) {
    fl_color(active_r() ? color() : fl_inactive(color()));
    fl_begin_polygon(); fl_circle(0,0,14); fl_end_polygon();
    fl_color(active_r() ? FL_FOREGROUND_COLOR : fl_inactive(FL_FOREGROUND_COLOR));
    fl_begin_loop(); fl_circle(0,0,14); fl_end_loop();
  }

  fl_push_matrix();
  fl_translate(0.60, 0.60);
  drawhands(shadow_color, shadow_color);
  fl_pop_matrix();

  fl_push_matrix();
  fl_color(active_r() ? FL_FOREGROUND_COLOR : fl_inactive(FL_FOREGROUND_COLOR));
  for (int i=0; i<12; i++) {
    if (i==6) rect(-0.5, 9, 1, 2);
    else if (i==3 || i==0 || i== 9) rect(-0.5, 9.5, 1, 1);
    else rect(-0.25, 9.5, .5, 1);
    fl_rotate(-30);
  }
  fl_pop_matrix();

  drawhands(selection_color(), FL_FOREGROUND_COLOR);
  fl_pop_matrix();
}
