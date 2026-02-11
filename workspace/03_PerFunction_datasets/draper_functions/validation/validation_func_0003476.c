aurora_draw_menu_radiobutton (cairo_t * cr,
			      const AuroraColors * colors,
			      const WidgetParameters * widget,
			      const OptionParameters * status,
			      int x, int y, int width, int height)
{

  AuroraRGB bullet;

  width = height = 15;
  double center = width / 2.0 - 1.5;

  cairo_translate (cr, x-1.0, y);


  bullet = colors->text[widget->state_type];


  cairo_arc (cr, center + 1.5, center + 1.5, center, 0, M_PI * 2);

  cairo_set_source_rgb (cr, bullet.r, bullet.g, bullet.b);
  cairo_set_line_width(cr, 1.0);
  cairo_stroke (cr);

  if (status->draw_bullet) {
    if (status->inconsistent) {
      cairo_rectangle (cr, 3, 5, 7, 3);
    }
    else {
      cairo_arc (cr, center + 1.5, center + 1.5, center - 2.5, 0, M_PI * 2);
    }

    cairo_set_source_rgb (cr, bullet.r, bullet.g, bullet.b);
    cairo_fill (cr);
  }
}
