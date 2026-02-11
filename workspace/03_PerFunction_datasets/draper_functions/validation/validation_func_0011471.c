MultipressWindow() : Gtk::Window(), loop(Glib::MainLoop::create()) {
  set_position(Gtk::WIN_POS_CENTER);
  set_decorated(false);
  set_modal(true);
#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
  signal_key_press_event().connect(sigc::mem_fun(this, &MultipressWindow::on_key_press_event), false);
  signal_expose_event().connect(sigc::mem_fun(this, &MultipressWindow::on_expose_event), false);
#endif
}
