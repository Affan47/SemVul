bezier(dbl x1,dbl y1,dbl x2,dbl y2,dbl x3,dbl y3) {
	double x=g.curx,y=g.cury;
	if (g.inpath) {
		if (g.xinline==false) move(g.curx,g.cury);
		out() << x1 << " " << y1 << " " << x2 << " " << y2 << " "
		      << x3 << " " << y3 << " curveto" << endl;
	} else {
		g_flush();
		if (!g.xinline) out() << x << " " << y << " moveto ";
		out() << x1 << " " << y1 << " " << x2 << " " << y2 << " "
		      << x3 << " " << y3 << " curveto" << endl;
	}
	g.xinline = true;
}
