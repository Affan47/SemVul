draw() {
  draw_box();
  fl_push_matrix();
  fl_translate(x()+w()/2, y()+h()/2);
  fl_scale(w()/2, h()/2);
  fl_color(FL_BLACK);
  for (int i = 0; i < 20; i++) {
    for (int j = i+1; j < 20; j++) {
      fl_begin_line();
      fl_vertex(cos(M_PI*i/10+.1), sin(M_PI*i/10+.1));
      fl_vertex(cos(M_PI*j/10+.1), sin(M_PI*j/10+.1));
      fl_end_line();
    }
  }
  fl_pop_matrix();
}
