set_dpi(Coord& pixel) {
    String s;
    if (style_->find_attribute("dpi", s)) {
	long dpi;
	if (s.convert(dpi) && dpi != 0) {
	    pixel = 72.0 / float(dpi);
	}
    } else {
	pixel = 72.0 / 75.0;
    }
}
