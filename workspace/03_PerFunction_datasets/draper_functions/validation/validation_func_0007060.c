on_expose_event(GdkEventExpose* event)
{
  double p = (pos + 1.0)/2.0;
  if (0)
    {
      get_window()->draw_rectangle(get_style()->get_fg_gc(get_state()),
                                   true,
                                   (get_allocation().get_width() * p) - 4, 0,
                                   9, get_allocation().get_height()-1);
    }

  Glib::RefPtr<Gdk::Window> window = get_window();
  if(window)
    {
      Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

      int w  = get_allocation().get_width()-10;
      int h  = get_allocation().get_height()-10;

      cr->translate(5, 5);


      cr->set_source_rgb(0.0, 0.0, 0.0);
      cr->set_line_width(1.0);
      cr->rectangle(0, 0, w, h);
      cr->stroke();

      cr->set_source_rgba(0.0, 0.0, 0.0, 0.5);
      cr->move_to(w/2, 0);
      cr->line_to(w/2, h);
      cr->stroke();

      cr->set_line_width(2.0);
      cr->set_source_rgb(0.0, 0.0, 0.0);
      cr->move_to(w * p, 0);
      cr->line_to(w * p, h);
      cr->stroke();
    }

  return true;
}
