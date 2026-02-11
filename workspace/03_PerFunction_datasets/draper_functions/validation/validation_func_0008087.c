draw_palace(Glib::RefPtr<Gdk::GC>& gc, int x, int y)
{
	int width;
	int height;
	get_grid_size(width, height);
	Gdk::Point p = get_coordinate(x, y);

	ui_pixmap->draw_line(gc, p.get_x() - width, p.get_y() - height, p.get_x() + width, p.get_y() + height);
	ui_pixmap->draw_line(gc, p.get_x() + width, p.get_y() - height, p.get_x() - width, p.get_y() + height);
}
