box_fill(dbl x1, dbl y1, dbl x2, dbl y2) {
	if (g.inpath) {
		xdbox(x1,y1,x2,y2);
	} else {
		g_flush();
		cairo_new_path(m_cr);
		GLERectangle rect(x1, y1, x2, y2);
		xdbox(x1,y1,x2,y2);
		ddfill(&rect);
		cairo_new_path(m_cr);
	}
}
