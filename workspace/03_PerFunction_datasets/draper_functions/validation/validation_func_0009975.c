fullscreen_cb(Fl_Widget *o, void *p) {
  Fl_Window *w = (Fl_Window *)p;
  int d = ((Fl_Button *)o)->value();
  if (d) {
    px = w->x();
    py = w->y();
    pw = w->w();
    ph = w->h();
    w->fullscreen();
    w->override();
#ifndef WIN32
    border_button->value(w->border());
#endif
  } else {

    w->fullscreen_off();
  }
}
