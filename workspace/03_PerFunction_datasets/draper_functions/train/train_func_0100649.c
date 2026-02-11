line(double zx,double zy) {
	if (g.xinline==false) {
		move(g.curx,g.cury);
	}
	cairo_line_to(m_cr, zx, zy);
}
